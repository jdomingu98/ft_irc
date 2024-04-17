#include "TopicCommand.hpp"

/**
 * Constructs a new TopicCommand.
 * 
 * @param channel The channel where the topic will be set, removed or requested
 */
TopicCommand::TopicCommand(Channel *channel) : ACommand(true), _channel(channel), _topic(NONE), _newTopicProvided(false) {}

/**
 * Constructs a new TopicCommand.
 * 
 * @param channel The channel where the topic will be set, removed or requested
 * @param topic The topic of the channel
 */
TopicCommand::TopicCommand(Channel *channel, const std::string& topic) : ACommand(true), _channel(channel), _topic(topic), _newTopicProvided(true) {}

/**
 * Destroys the TopicCommand.
 */
TopicCommand::~TopicCommand() {}


/**
 * Executes the command TOPIC.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NotOnChannelException` if the user is not on the channel
 * @throws `ChanOPrivsNeededException` if the user is not an operator of the channel
 */
void TopicCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);

    std::string channelName = _channel->getName();
    std::string nickname = user.getNickname();
    std::string username = user.getUsername();
    std::string hostname = user.getHostname();

    if (!user.isOnChannel(channelName))
        throw NotOnChannelException(channelName);
    
    Logger::debug("User in channel " + channelName);

    if (_newTopicProvided) {
        if (_channel->isTopicProtected() && !_channel->isOper(nickname))
            throw ChanOPrivsNeededException(channelName);

        Logger::debug("Setting the new channel topic to " + _topic);
        _channel->setTopic(_topic);

        Logger::debug("Sending topic to all channel users");
        _channel->broadcastToChannel(TOPIC_MSG(nickname, username, hostname, channelName, _topic));
    }
    else {
        Logger::debug("Sending topic to user");
        server.sendMessage(clientFd, RPL_TOPIC(channelName, _channel->getTopic()));
    }
    
    Logger::debug("Channel's topic is: " + _channel->getTopic());
}