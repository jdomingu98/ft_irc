#include "PrivateMessageCommand.hpp"

PrivateMessageCommand::PrivateMessageCommand(std::vector<std::string> receivers, std::string message)
  : ICommand(true), _receivers(receivers), _message(message) {}

void PrivateMessageCommand::execute(Server &server, int fd) {
    User sender = server.getUserByFd(fd);
    Logger::debug("Sending private message from " + sender.getNickname());

    for (size_t i = 0; i < this->_receivers.size(); i++) {
        try {
          User destinationUser = server.getUserByNickname(this->_receivers[i]);
          sender.sendPrivateMessageToUser(server, destinationUser, this->_message);
        } catch (const ServerException &e) {
          // Uno de los usuarios no existe, deberiamos de cortar la ejecucion del comando?
          // throw NoSuchNickException(receiver);
          server.sendMessage(fd, e.what());
        }
    }
}

