#include"NickCommand.hpp"


NickCommand::NickCommand(): _nickname("") {}

NickCommand::NickCommand(const std::string& nickname): _nickname(nickname) {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Server &server, int fd) {
    if (this->_nickname.empty())
        throw CommandException("NICK COMMAND: Empty nickname.");

    if (this->_nickname.size() > 9)
        throw CommandException("NICK COMMAND: Nickname is too long.");

    if (server.isNicknameInUse(this->_nickname))
        throw CommandException("NICK COMMAND: Nickname is already in use.");

    if (!NickCommand::isValidNickname())
        throw CommandException("NICK COMMAND: Invalid nickname.");

    User user = server.getUserByFd(fd);
    user.setNickname(this->_nickname);
}

bool NickCommand::isValidNickname() {
    for (size_t i = 0; i < this->_nickname.size(); i++) {
        if ((!std::isalnum(this->_nickname[i]) && this->_nickname[i] != '_' )
            || this->_nickname[i] == ' ' || this->_nickname[i] == '\r' || this->_nickname[i] == '\n')
            return false;
    }
    return true;
}