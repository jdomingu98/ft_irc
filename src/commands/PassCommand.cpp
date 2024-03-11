#include "PassCommand.hpp"

PassCommand::PassCommand(): _password("") {}

PassCommand::PassCommand(const std::string& password): _password(password) {}

PassCommand::~PassCommand() {}

void PassCommand::execute(Server &server, int fd) {
  std::cout << "Password: " << _password << std::endl;
    if (server.isValidPassword(this->_password)) {
      server.getUserByFd(fd).checkPassword();
    } else {
      throw CommandException("Invalid password");
    }
}
