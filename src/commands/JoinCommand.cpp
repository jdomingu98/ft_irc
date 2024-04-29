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
 * Prints the users in the channel.
 * 
 * @param channel The channel to print the users from
 */
void JoinCommand::printUsers(Channel &channel) const {
    Logger::debug("OPERATORS:");
    std::vector<User *> opers = channel.getOperators();
    for (size_t i = 0; i < opers.size(); i++)
        Logger::debug(opers[i]->getNickname());

    Logger::debug("USERS:");
    std::vector<User *> users = channel.getUsers();
    for (size_t i = 0; i < users.size(); i++)
        Logger::debug(users[i]->getNickname());
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
    std::vector<User *> channelUsers = channel.getAllUsers();

    std::string nickname = user.getNickname();
    std::string username = user.getUsername();
    std::string hostname = user.getHostname();

    for (size_t i = 0; i < channelUsers.size(); i++) {
        server.sendMessage(channelUsers[i]->getFd(),
                            CMD_MSG(nickname, username, hostname, JOIN_MSG(channelName)));
    }

    if (!channel.getTopic().empty())
        server.sendMessage(clientFd, TopicResponse(nickname, channelName, channel.getTopic()).getReply());
    server.sendMessage(clientFd, NamesReplyResponse(nickname, channel).getReply());
    server.sendMessage(clientFd, EndOfNamesResponse(nickname, channelName).getReply());
}

/**
 * Executes the command JOIN.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `BadChannelMaskException` If the channel mask is invalid
 * @throws `TooManyChannelsException` If the user is in too many channels
 * @throws `InviteOnlyChanException` If the channel is invite-only
 * @throws `BadChannelKeyException` If the channel key is incorrect
 * @throws `ChannelIsFullException` If the channel is full
 * @throws `UserOnChannelException` If the user is already on the channel
 * 
 */
void JoinCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);

    std::string nickname = user.getNickname();
    Logger::debug("JOINING CHANNELS");

    std::string channelName;
    std::string channelKey;
    bool isNewChannel = false;

    for (std::map<std::string, std::string>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
        channelName = it->first;
        channelKey = it->second;

        try {
            if (channelName[0] != '#' && channelName[0] != '&')
                throw BadChannelMaskException(channelName);
        } catch (IRCException &e) {
            server.sendExceptionMessage(clientFd, e);
            continue;

        }
        // Check if user has joined max channels
        if (user.isUserInMaxChannels())
            throw TooManyChannelsException(channelName);


        isNewChannel = false;
        if (!server.channelExists(channelName)) {
            isNewChannel = true;
            server.addChannel(Channel(channelName, user));
        }

        Channel &channel = server.getChannelByName(channelName); //No need to catch exception

        if (!isNewChannel && channel.isUserInChannel(nickname))
            throw UserOnChannelException(nickname, channelName);

        //1. Check if channel[i] is invite-only channel and if user is invited
        if (channel.isInviteOnly() && !channel.isUserInvited(nickname))
            throw InviteOnlyChanException(channelName);

        //2. Check if password is correct if channel[i] is password-protected
        if (channel.isPasswordSet() && channel.getPassword() != channelKey)
            throw BadChannelKeyException(channelName);

        //3. Check if channel[i] has limit and if its full
        if (channel.hasLimit() && channel.isFull())
            throw ChannelIsFullException(channelName);


        Logger::debug("--- PRE SAVE ---");
        this->printUsers(channel);

        if (!isNewChannel)
            channel.addUser(user);
        user.addChannel(channel);

        Logger::debug("--- POST SAVE ---");
        this->printUsers(channel);

        //5. Send JOIN messages
        sendMessages(clientFd, channel);
    }
}