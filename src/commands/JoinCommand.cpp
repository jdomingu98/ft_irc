#include "JoinCommand.hpp"

/**
 * Constructs a new JoinCommand.
 * 
 * @param channels The map of channels to be joined.
 */
JoinCommand::JoinCommand(const std::map<std::string, std::string> channels)
    : ACommand(true), _channels(channels) {}

/**
 * Sends the join message and responses to the client.
 * 
 * @param clientFd The socket file descriptor of the client
 * @param channel The channel to send the message to
 * 
 */
void JoinCommand::sendMessages(int clientFd, const Channel &channel) const {
    Server &server = Server::getInstance();
    User *user = server.getUserByFd(clientFd);

    const std::string &channelName = channel.getName();
    const std::vector<User *> allUsers = channel.getAllUsers();

    const std::string &nickname = user->getNickname();
    for (std::vector<User *>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it)
        server.sendMessage((*it)->getFd(),
                        CMD_MSG(nickname, user->getUsername(), user->getHostname(), JOIN_MSG(channelName)));

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
    User *user = server.getUserByFd(clientFd);
	for (size_t i = 0; i < server.getUsers().size(); i++) {
		std::cout << "User fd[" << &server.getUsers()[i] << "]: " << server.getUsers()[i]->getFd() << std::endl;
	}

    const std::string &nickname = user->getNickname();

    std::map<std::string, std::string>::const_iterator it;
    Logger::debug("A");
    for (it = _channels.begin(); it != _channels.end(); it++) {
        const std::string &name = it->first;
        std::string key = it->second;
    Logger::debug("B");

        bool isNewChannel = false;
        try {
            if (name[0] != '#' && name[0] != '&')
                throw BadChannelMaskException(name);
    Logger::debug("C");

            // 1. Check if user has joined max channels
            if (user->isUserInMaxChannels())
                throw TooManyChannelsException(name);
    Logger::debug("D");

            if (!server.channelExists(name)) {
                isNewChannel = true;
                Channel c = Channel(name, user);
				std::cout << "userfd: " << user->getFd() << std::endl;
                server.addChannel(c);
            }
    Logger::debug("E");

            Channel &channel = server.getChannelByName(name);
			std::cout << "REF: " << &channel << std::endl;
			std::cout << "User fd returned" << channel.getOperators()[0]->getFd() << std::endl;
    Logger::debug("EEEEEEEEEEEG");
            if (!isNewChannel && user->isOnChannel(name))
                throw UserOnChannelException(nickname, name);
    Logger::debug("F");

            //2. Check if channel[i] is invite-only channel and if user is invited
            if (channel.isInviteOnly() && !channel.isUserInvited(nickname))
                throw InviteOnlyChanException(name);
    Logger::debug("G");

            //3. Check if password is correct if channel[i] is password-protected
            if (channel.isPasswordSet() && channel.getPassword() != key)
                throw BadChannelKeyException(name);
    Logger::debug("EH");

            //4. Check if channel[i] has limit and if its full
            if (channel.hasLimit() && channel.isFull())
                throw ChannelIsFullException(name);
    Logger::debug("I");

            if (!isNewChannel)
                channel.addUser(user);
                    Logger::debug("J");

            user->addChannel(&channel);
    Logger::debug("K");

            //5. Send JOIN messages
            sendMessages(clientFd, channel);
    Logger::debug("L");
        } catch (IRCException &e) {
            server.sendExceptionMessage(clientFd, e);
            continue;
        }
    }
}