#include "PrivateMessageCommand.hpp"

/**
 * PrivateMessageCommand password constructor.
 * 
 * @param receivers The users or channels that will receive the message
 * @param message The message to be sent
 */
PrivateMessageCommand::PrivateMessageCommand(std::vector<std::string> receivers, std::string message)
    : ACommand(true), _receivers(receivers), _message(message) {}

/**
 * Execute the command PRIVMSG.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NoSuchNickException` if the user does not exist
 * @throws `NoSuchChannelException` if the channel does not exist
 */
void PrivateMessageCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &sender = server.getUserByFd(clientFd);

    Logger::debug("Sending private message from " + sender.getNickname());
    for (size_t i = 0; i < this->_receivers.size(); i++) {
        try {
            if (this->_receivers[i][0] == '#' || this->_receivers[i][0] == '&') {
                Logger::debug("Sending private message to channel " + this->_receivers[i]);

                Channel &destinationChannel = server.getChannelByName(this->_receivers[i]);
                if (!destinationChannel.isUserInChannel(sender.getNickname()))
                    throw NoSuchNickException(this->_receivers[i]);

                std::vector<User *> usersChannel = destinationChannel.getAllUsers();
                std::vector<User *>::iterator it = std::find(usersChannel.begin(), usersChannel.end(), &sender);
                if (it != usersChannel.end())
                    usersChannel.erase(it);
                sender.broadcastToChannel(usersChannel, PRIVMSG_MSG(sender.getNickname(), this->_message));
                sender.sendPrivateMessageToChannel(destinationChannel, this->_message);
            } else {
                std::vector<User *> userOnly;
                userOnly.push_back(&server.getUserByNickname(this->_receivers[i]));
                sender.broadcastToChannel(userOnly, PRIVMSG_MSG(sender.getNickname(), this->_message));
            }
        } catch (const NoSuchChannelException &e) {
            Logger::debug("Channel " + this->_receivers[i] + " does not exist.");
            server.sendExceptionMessage(clientFd, e);
        } catch (const NoSuchNickException &e) {
            server.sendExceptionMessage(clientFd, e);
        }
    }
}