#include "JoinCommand.hpp"

/**
 * Constructs a new JoinCommand.
 * 
 * @param channelMap The map of channels to be joined.
 */
JoinCommand::JoinCommand(std::map<std::string, std::string> channelMap)
    : ICommand(true), _channels(channelMap) {}

/**
 * Destroys the JoinCommand.
 */
JoinCommand::~JoinCommand() {
    this->_channels.clear();
}

/** ----------------TESTING-------------
 * JOIN (#/&)channel password -> joins channel with password if it's correct
 * JOIN #c1,#c2 password -> password for c1, none for c2
 * JOIN #c1,#c2 password, -> password for c1, none for c2 ???
 * JOIN #c1,#c2 password1,password2 -> password1 for c1, password2 for c2
 * JOIN #c1,#c2 ,password -> none for c1, password for c2??
 * JOIN #c1,,#c2 password1,,password2 -> ignored "channel" between commas
 * JOIN #c1,,#c2 password1,password2 -> idk what happens here ¿¿¿???
 */

/**
 * Executes the command JOIN.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 */
void JoinCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);
    
    std::string nickname = user.getNickname();
    std::string username = user.getUsername();
    std::string hostname = user.getHostname();
    Logger::debug("JOINING CHANNELS");

    std::string channelName;
    std::string channelKey;

    for (std::map<std::string, std::string>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
        channelName = it->first;
        channelKey = it->second;
        Logger::debug("JOINING CHANNEL: " + channelName);
        Logger::debug("WITH KEY: " + channelKey);

        //0. If channel[i] does not exist, create it
        if (!server.channelExists(channelName)) {
            Logger::debug("CHANNEL DOES NOT EXIST");
            Channel newChannel(channelName, user);
            server.addChannel(newChannel);
            if (channelKey != "")
                server.getChannelByName(channelName).setPassword(channelKey);
        }

        Logger::debug("CHANNEL NOW EXISTS");
        Channel &channel = server.getChannelByName(channelName);
        Logger::debug("CHANNEL NAME: " + channel.getName());
        //1. Check if channel[i] is invite-only channel and if user is invited -> ERR_INVITEONLYCHAN
        /*if (channel.isInviteOnly() && !channel.isUserInvited(nickname)) {
            throw InviteOnlyChanException(channel.getName());
        }*/

        //2. Check if user's nick/username/hostname is banned from channel[i] -> ERR_BANNEDFROMCHAN
        /*if (channel.isUserBanned(nickname, username, hostname)) {
            throw BannedFromChanException(channel.getName());
        }*/

        //3. Check if password is correct if channel[i] is password-protected
        if (channel.isPasswordSet() && channel.getPassword() != channelKey) {
            throw BadChannelKeyException(channel.getName());
        }

        //4. Check if channel[i] has limit and if its full
        if (channel.hasLimit() && channel.isFull()) {
            throw ChannelIsFullException(channel.getName());
        }

        //5. Check if user has joined max channels
        if (user.isUserInMaxChannels()) {
            throw TooManyChannelsException(channel.getName());
        }
        Logger::debug("... PRE SAVE");
        Logger::debug("OPERATORS:");
        for (std::vector<User>::iterator it = channel.getOperators().begin(); it != channel.getOperators().end(); it++) {
            Logger::debug(it->getNickname());
        }
        Logger::debug("USERS:");
        std::vector<User> users = channel.getUsers();
        for (size_t i = 0; i < users.size(); i++) {
            Logger::debug(users[i].getNickname());
        }

        if (!channel.isUserInChannel(nickname))
            channel.addUser(user);
        Logger::debug("--- POST SAVE");
        Logger::debug("OPERATORS:");
        for (std::vector<User>::iterator it = channel.getOperators().begin(); it != channel.getOperators().end(); it++) {
            Logger::debug(it->getNickname());
        }
        Logger::debug("USERS:");
        users = channel.getUsers();
        for (size_t i = 0; i < users.size(); i++) {
            Logger::debug(users[i].getNickname());
        }
        
        user.addChannel(channel);

        //6. Send JOIN message to all users in channel[i] ¿?
        //server.sendMessage(clientFd, RPL_TOPIC(channel.getName(), channel.getTopic()));
        //server.sendMessage(clientFd, RPL_NAMREPLY(channel.getName(), channel.getAllUsers()));
    }
}