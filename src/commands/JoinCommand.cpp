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

/**
 * Returns the RPL_NAMREPLY message.
 * 
 * @param channelName The name of the channel
 * @param opers The vector of operators in the channel
 * @param users The vector of users in the channel
 * 
 * @return The RPL_NAMREPLY message
 */
std::string JoinCommand::rplNamReply(std::string const &channelName, std::vector<User> const &opers, std::vector<User> const &users) const {
    std::string msg = channelName + " :@" + opers[0].getNickname();

    for (size_t i = 1; i < opers.size(); i++) {
        msg += " @" + users[i].getNickname();
    }

    for (size_t i = 0; i < users.size(); i++) {
        msg += " +" + users[i].getNickname();
    }

    return msg;
}

void JoinCommand::printUsers(Channel &channel) const {
    Logger::debug("OPERATORS:");
    std::vector<User> opers = channel.getOperators();
    for (size_t i = 0; i < opers.size(); i++) {
        Logger::debug(opers[i].getNickname());
    }
    
    Logger::debug("USERS:");
    std::vector<User> users = channel.getUsers();
    for (size_t i = 0; i < users.size(); i++) {
        Logger::debug(users[i].getNickname());
    }
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
    Channel channel;
    
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

        //1. If channel[i] does not exist, create it
        if (!server.channelExists(channelName)) {
            Logger::debug("CHANNEL DOES NOT EXIST");
            Channel newChannel(channelName, user);
            server.addChannel(newChannel);
            channel = server.getChannelByName(channelName);
            if (!channelKey.empty())
                channel.setPassword(channelKey);
        } else {
            Logger::debug("CHANNEL NOW EXISTS");
            channel = server.getChannelByName(channelName);
            Logger::debug("CHANNEL NAME: " + channel.getName());

            //2. Check if channel[i] is invite-only channel and if user is invited
            if (channel.isInviteOnly() && !channel.isUserInvited(nickname))
                throw InviteOnlyChanException(channel.getName());

            //3. Check if password is correct if channel[i] is password-protected
            if (channel.isPasswordSet() && channel.getPassword() != channelKey)
                throw BadChannelKeyException(channel.getName());

            //4. Check if channel[i] has limit and if its full
            if (channel.hasLimit() && channel.isFull())
                throw ChannelIsFullException(channel.getName());

            //5. Check if user has joined max channels
            if (user.isUserInMaxChannels())
                throw TooManyChannelsException(channel.getName());

            Logger::debug("--- PRE SAVE ---");
            this->printUsers(channel);

            if (!channel.isUserInChannel(nickname))
                channel.addUser(user);

            Logger::debug("--- POST SAVE ---");
            this->printUsers(channel);
        }

        user.addChannel(channel);

        //6. Send JOIN message to all users in channel[i]
        std::string topic = channel.getTopic();
        const std::string message = topic.empty()   ? RPL_NO_TOPIC(channel.getName())
                                                    : RPL_TOPIC(channel.getName(), topic);
        
        server.sendMessage(clientFd, message);
        server.sendMessage(clientFd, rplNamReply(channel.getName(), channel.getOperators(), channel.getUsers()));
        server.sendMessage(clientFd, RPL_END_OF_NAMES(channel.getName()));
    }
}