#include"NickCommand.hpp"


NickCommand::NickCommand(): _nickname("") {}

NickCommand::NickCommand(const std::string& nickname): _nickname(nickname) {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Server &server, int fd) {
    User user = server.getUserByFd(fd);
    user.setNickname(this->_nickname);
}