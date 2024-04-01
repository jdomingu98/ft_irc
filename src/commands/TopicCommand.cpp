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
    Channel *channel = user.getChannelByName(this->_channelName);
    
    if (channel == NULL)
        throw ServerException("You're not on that channel");

    if (_topic.empty()){
        //TODO: Send the topic to the user
    }
    else if (channel->getName() == _channelName && user.isUserAnOper(_channelName)){
            channel->setTopic(_topic);
            std::cout << "estoy aqui" << std::endl;
            //TODO:(channel, ":" + user.getNickname() + " TOPIC " + channel.getName() + " :" + _topic);
        }
        else {
            //TODO: You're not channel operator"
        }
    //TODO: set/remove with cmd MODE (flag +t)
    std::cout << "Topic command executed" << std::endl;
}