#include "NickCommand.hpp"

/**
 * NickCommand default constructor.
 */
NickCommand::NickCommand(): _nickname("") {}

/**
 * NickCommand nickname constructor.
 * 
 * @param nickname The nickname
 */
NickCommand::NickCommand(const std::string& nickname): _nickname(nickname) {}

/**
 * NickCommand destructor.
 */
NickCommand::~NickCommand() {}

/**
 * Execute the command NICK.
 * 
 * @param server The server where the command will be executed
 * @param fd The socket file descriptor of the client
 * 
 * @throws `CommandException` If the nickname is empty, too long, already in use or invalid
 * 
 */
void NickCommand::execute(Server &server, int fd) {
    if (this->_nickname.empty())
        throw CommandException("NICK COMMAND: Empty nickname.");

    if (this->_nickname.size() > MAX_NICKNAME_SIZE)
        throw CommandException("NICK COMMAND: Nickname is too long.");

    if (server.isNicknameInUse(this->_nickname))
        throw CommandException("NICK COMMAND: Nickname is already in use.");

    if (!NickCommand::isValidNickname())
        throw CommandException("NICK COMMAND: Invalid nickname.");

    User user = server.getUserByFd(fd);
    user.setNickname(this->_nickname);
}

/**
 * Check if the nickname is valid.
 * A nickname is valid if it contains only alphanumeric characters and underscores.
 * 
 * @return `true` if the nickname is valid, `false` otherwise
 */
bool NickCommand::isValidNickname() {
    for (size_t i = 0; i < this->_nickname.size(); i++) {
        if (!std::isalnum(this->_nickname[i]) && this->_nickname[i] != '_' )
            return false;
    }
    return true;
}