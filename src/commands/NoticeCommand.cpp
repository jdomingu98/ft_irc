#include "NoticeCommand.hpp"

/**
 * NoticeCommand password constructor.
 * 
 * @param receivers The users or channels that will receive the message
 * @param message The message to be sent
 */
NoticeCommand::NoticeCommand(std::vector<std::string> receivers, std::string message)
    : ACommand(true), _receivers(receivers), _message(message) {}

/**
 * Execute the command NOTICE.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `IgnoreCommandException` if some error occurs
 * 
 */
void NoticeCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &sender = server.getUserByFd(clientFd);

    Logger::debug("Sending notice from " + sender.getNickname());
    for (size_t i = 0; i < this->_receivers.size(); i++) {
        try {
            if (this->_receivers[i][0] == '#' || this->_receivers[i][0] == '&') {
                Logger::debug("Sending notice to channel " + this->_receivers[i]);

                Channel &destinationChannel = server.getChannelByName(this->_receivers[i]);
                if (!destinationChannel.isUserInChannel(sender.getNickname()))
                    throw IgnoreCommandException();

                std::vector<User *> usersChannel = destinationChannel.getAllUsers();
                std::vector<User *>::iterator it = std::find(usersChannel.begin(), usersChannel.end(), &sender);
                if (it != usersChannel.end())
                    usersChannel.erase(it);
                sender.broadcastToChannel(usersChannel, NOTICE_MSG(sender.getNickname(), this->_message));
            } else {
                std::vector<User *> userOnly;
                userOnly.push_back(&server.getUserByNickname(this->_receivers[i]));
                sender.broadcastToChannel(userOnly, NOTICE_MSG(sender.getNickname(), this->_message));
            }
        } catch (const IRCException &e) {
            throw IgnoreCommandException();
        }
    }
}