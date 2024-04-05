#include "TopicCommand.hpp"

/**
 * Constructs a new TopicCommand.
 * 
 * @param channel The channel where the topic will be set, removed or requested
 */
TopicCommand::TopicCommand(Channel *channel) : ICommand(true), _channel(channel), _topic(NONE) {}

/**
 * Constructs a new TopicCommand.
 * 
 * @param channel The channel where the topic will be set, removed or requested
 * @param topic The topic of the channel
 */
TopicCommand::TopicCommand(Channel *channel, const std::string& topic) : ICommand(true), _channel(channel), _topic(topic) {}

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

    //Check the validation order with official IRC server

    if (!user.isOnChannel(channelName))
            throw NotOnChannelException(channelName);
    Logger::debug("User in channel " + channelName);

    /*TODO: set/remove with MODE command (flag +t)
    if (!_channel->isOper(user.getNickname())) 
        throw ChanOPrivsNeededException(channelName);
    Logger::debug("User " + user.getNickname() + " is operator in channel " + channelName);*/
    if (_topic.empty()) { 
        Logger::debug("Channel's topic is empty.");
        // TODO: Send RPL_NO_TOPIC to user (No es seguro, es lo que he intuido)
    } else {
        Logger::debug("Channel's topic not empty.");
        Logger::debug("Setting the new channel topic to " + _topic);
        _channel->setTopic(_topic);
        // TODO: Send RPL_TOPIC to user (No es seguro, es lo que he intuido)
    }

    Logger::debug("Channel's topic is: " + _channel->getTopic());
    
    // TODO:(channel, ":" + user.getNickname() + " TOPIC " + channel.getName() + " :" + _topic);
}