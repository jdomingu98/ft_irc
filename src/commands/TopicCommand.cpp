#include "TopicCommand.hpp"

/**
 * Constructs a new TopicCommand.
 * 
 * @param channel The channel where the topic will be requested
 */
TopicCommand::TopicCommand(Channel *channel) : ACommand(true), _channel(channel), _topic(NONE), _newTopicProvided(false) {}

/**
 * Constructs a new TopicCommand.
 * 
 * @param channel The channel where the topic will be set or removed
 * @param topic The new topic of the channel
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

    std::string channelName = this->_channel->getName();
    std::string nickname = user.getNickname();

    if (!user.isOnChannel(channelName))
        throw NotOnChannelException(channelName);

    if (this->_newTopicProvided && this->_channel->isTopicProtected() && !this->_channel->isOper(nickname))
        throw ChanOPrivsNeededException(channelName);

    if (this->_newTopicProvided) {
        Logger::debug("Setting the new topic of channel " + channelName + " to " + this->_topic);
        this->_channel->setTopic(this->_topic);
        user.broadcastToChannel(this->_channel->getAllUsers(), TOPIC_MSG(channelName, this->_topic));
    } else {
        std::string message = this->_channel->getTopic().empty()    ? NoTopicResponse(nickname, channelName).getReply()
                                                                    : TopicResponse(nickname, channelName, this->_channel->getTopic()).getReply();
        Logger::debug("Sending topic of channel " + channelName + " response to user " + nickname);
        server.sendMessage(clientFd, message);
    }
    Logger::debug("Channel " + channelName + " topic is: " + this->_channel->getTopic());
}