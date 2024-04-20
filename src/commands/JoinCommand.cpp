#include "JoinCommand.hpp"

/**
 * Constructs a new JoinCommand.
 * 
 * @param channelMap The map of channels to be joined.
 */
JoinCommand::JoinCommand(std::map<std::string, std::string> channelMap)
    : ACommand(true), _channels(channelMap) {}

/**
 * Destroys the JoinCommand.
 */
JoinCommand::~JoinCommand() {
    this->_channels.clear();
}

/**
 * Returns the RPL_NAMREPLY message.
 * 
 * @param channelName The name of the channel
 * @param opers The vector of operators in the channel
 * @param users The vector of users in the channel
 * 
 * @return The RPL_NAMREPLY message
 */
std::string JoinCommand::rplNamReply(const std::string &nickname,
                                        const std::string &username,
                                        const std::string &hostname,
                                        const Channel &channel) const {

    std::string channelName = channel.getName();
    std::string msg = USER_ID(nickname, username, hostname) + " " + channelName + " :";


    std::vector<User> users = channel.getUsers();
    std::vector<User> opers = channel.getOperators();
    
    if (opers.size() > 0) {
        msg += "@" + opers[0].getNickname();

        for (size_t i = 1; i < opers.size(); i++)
            msg += " @" + opers[i].getNickname();

        for (size_t i = 0; i < users.size(); i++)
            msg += " " + users[i].getNickname();
    } else if (users.size() > 0) {
        msg += users[0].getNickname();

        for (size_t i = 1; i < users.size(); i++)
            msg += " " + users[i].getNickname();
    }

    return msg;
}

void JoinCommand::printUsers(Channel &channel) const {
    Logger::debug("OPERATORS:");
    std::vector<User> opers = channel.getOperators();
    for (size_t i = 0; i < opers.size(); i++)
        Logger::debug(opers[i].getNickname());
    
    Logger::debug("USERS:");
    std::vector<User> users = channel.getUsers();
    for (size_t i = 0; i < users.size(); i++)
        Logger::debug(users[i].getNickname());
}

/**
 * Sends the join message and responses to the client.
 * 
 * @param clientFd The socket file descriptor of the client
 * @param message The message to be sent
 * @param channel The channel to send the message to
 * 
 */
void JoinCommand::sendMessages(int clientFd, Channel &channel) const {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);

    std::string channelName = channel.getName();
    std::vector<User> channelUsers = channel.getAllUsers();
    
    std::string nickname = user.getNickname();
    std::string username = user.getUsername();
    std::string hostname = user.getHostname();
    
    for (size_t i = 0; i < channelUsers.size(); i++) {
        server.sendMessage(channelUsers[i].getFd(),
                            JOIN_MSG(channelUsers[i].getNickname(), channelUsers[i].getUsername(),
                                    channelUsers[i].getHostname(), channelName));
    }
    server.sendMessage(clientFd, rplNamReply(nickname, username, hostname, channel));
    server.sendMessage(clientFd, RPL_END_OF_NAMES(nickname, username, hostname, channelName));
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

        Logger::debug("JOINING CHANNEL: " + channelName + " WITH KEY: " + channelKey);

        if (!server.channelExists(channelName)) {
            Logger::debug("CHANNEL DOES NOT EXIST");

            server.addChannel(Channel(channelName, user));
            Channel &channel = server.getChannelByName(channelName);

            user.addChannel(channel);
            this->printUsers(channel);
            
            sendMessages(clientFd, channel);
            continue;
        }

        Logger::debug("CHANNEL NOW EXISTS");
        Channel &channel = server.getChannelByName(channelName);
        Logger::debug("CHANNEL NAME: " + channelName);
        
        if (channel.isUserInChannel(nickname))
            throw UserOnChannelException(nickname, channelName); //Provisional

        //1. Check if channel[i] is invite-only channel and if user is invited
        if (channel.isInviteOnly() && !channel.isUserInvited(nickname))
            throw InviteOnlyChanException(channelName);

        //2. Check if password is correct if channel[i] is password-protected
        if (channel.isPasswordSet() && channel.getPassword() != channelKey)
            throw BadChannelKeyException(channelName);

        //3. Check if channel[i] has limit and if its full
        if (channel.hasLimit() && channel.isFull())
            throw ChannelIsFullException(channelName);

        //4. Check if user has joined max channels
        if (user.isUserInMaxChannels())
            throw TooManyChannelsException(channelName);

        Logger::debug("--- PRE SAVE ---");
        this->printUsers(channel);

        channel.addUser(user);
        user.addChannel(channel);

        Logger::debug("--- POST SAVE ---");
        this->printUsers(channel);

        //5. Send JOIN messages
        sendMessages(clientFd, channel);
    }
}