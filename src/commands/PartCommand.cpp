#include "PartCommand.hpp"

/**
 * Constructs a new PartCommand.
 * 
 * @param channels The vector of channels to be left.
 */
PartCommand::PartCommand(std::vector<std::string> channels) : ACommand(true), _channels(channels) {}

/**
 * Destroys the PartCommand.
 */
PartCommand::~PartCommand() {
    this->_channels.clear();
}

/**
 * Executes the command PART.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NotOnChannelException` if the user is not on the channel.
 * @throws `NoSuchChannelException` if the channel does not exist.
 * 
 */
void PartCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);

    std::string nickname = user.getNickname();
    for (size_t i = 0; i < this->_channels.size(); i++) {
        try {
            Channel &channel = server.getChannelByName(this->_channels[i]);
            
            if (!user.isOnChannel(this->_channels[i]))
                throw NotOnChannelException(this->_channels[i]);
            Logger::debug("User in channel " + this->_channels[i] + ". Added to PART list.");

            user.broadcastToChannel(channel.getAllUsers(), PART_MSG(channel.getName()), server.sendMessage);
            channel.removeUser(nickname);
            Logger::debug("User " + nickname + " removed from channel " + this->_channels[i] + ".");
        } catch (NoSuchChannelException &e) {
            Logger::debug("Channel " + this->_channels[i] + " does not exist.");
            server.sendExceptionMessage(clientFd, e);
        }
    }
}