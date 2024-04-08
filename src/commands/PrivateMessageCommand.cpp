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
 * @throws `ServerException` no se que pasa si no se encuentra el usuario ///
 */
void PrivateMessageCommand::execute(int clientFd) {
    Server& server = Server::getInstance();
    User sender = server.getUserByFd(clientFd);
    Logger::debug("Sending private message from " + sender.getNickname());

    for (size_t i = 0; i < this->_receivers.size(); i++) {
        try {
            User destinationUser = server.getUserByNickname(this->_receivers[i]);
            sender.sendPrivateMessageToUser(destinationUser, this->_message);
        } catch (const ServerException &e) {
          // Uno de los usuarios no existe, deberiamos de cortar la ejecucion del comando?
          // throw NoSuchNickException(receiver);
            server.sendMessage(clientFd, e.what());
        }
    }
}

