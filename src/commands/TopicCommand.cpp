#include "TopicCommand.hpp"

/**
 * Topic command constructor
 * 
 * @param channelName 
 */
TopicCommand::TopicCommand(const std::string& channelName) : ICommand(true), _channelName(channelName) {}

/**
 * Topic command constructor
 * 
 * @param channelName 
 * @param topic 
 */
TopicCommand::TopicCommand(const std::string& channelName, const std::string& topic) : ICommand(true), _channelName(channelName), _topic(topic) {}

/**
 * Topic command destructor
 */
TopicCommand::~TopicCommand() {}


/**
 * This function aims to execute the topic command.
 * 
 * @param server The server where the command is being executed.
 * @param clientFd The client file descriptor that is executing the command.
 */
void TopicCommand::execute(int clientFd) {
    User user = Server::getInstance().getUserByFd(clientFd);
    Channel channel = user.findAndGetChannel(this->_channelName);

    if(_topic.empty()){
        //TODO: Send the topic to the user
    }
    else {
        if(channel.getName() == _channelName && user.isUserAnOper(_channelName)){
            channel.setTopic(_topic);
            //TODO:(channel, ":" + user.getNickname() + " TOPIC " + channel.getName() + " :" + _topic);
        }
        else {
            //TODO: You're not channel operator"
        }
    }
}