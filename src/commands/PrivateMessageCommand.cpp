#include "PrivateMessageCommand.hpp"

void PrivateMessageCommand::execute(Server &server, int fd) {
    User sender = server.getUserByFd(fd);
    std::cout << "Sending private message from " << sender.getNickname() << std::endl;

    for (size_t i = 0; i < this->_receivers.size(); i++) {
        try {
          User destinationUser = server.getUserByNickname(this->_receivers[i]);
          std::cout << "Sending private message to " << destinationUser.getNickname() << std::endl;
          sender.sendPrivateMessageToUser(server, destinationUser, this->_message);
        } catch (const ServerException &e) {
          // Uno de los usuarios no existe, deberiamos de cortar la ejecucion del comando?
          // throw NoSuchNickException(receiver);
          server.sendMessage(fd, e.what());
        }
    }
}

