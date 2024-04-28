#include "NickCommand.hpp"

/**
 * NickCommand default constructor.
 */
NickCommand::NickCommand() : ACommand(false),  _nickname(NONE) {}

/**
 * NickCommand nickname constructor.
 * 
 * @param nickname The nickname
 */
NickCommand::NickCommand(const std::string& nickname) : ACommand(false), _nickname(nickname) {}

/**
 * NickCommand destructor.
 */
NickCommand::~NickCommand() {}

/**
 * Execute the command NICK.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NoNicknameGivenException` If the nickname is empty
 * @throws `ErroneousNicknameException` If the nickname is too long or invalid
 * @throws `NicknameInUseException` If the nickname is already in use and the user is registered
 * 
 */
void NickCommand::execute(int clientFd) {
    Server& server = Server::getInstance();
    if (this->_nickname.empty())
        throw NoNicknameGivenException();

    if (this->_nickname.size() > MAX_NICKNAME_SIZE)
        throw ErroneousNicknameException(this->_nickname);

    User &user = server.getUserByFd(clientFd);

    if (server.isNicknameInUse(this->_nickname))
        throw NicknameInUseException(this->_nickname);

    if (!NickCommand::isValidNickname())
        throw ErroneousNicknameException(this->_nickname);

    user.setNickname(this->_nickname);
    if (!user.isRegistered() && user.canRegister())
        server.attemptUserRegistration(clientFd);
}

/**
 * Check if the nickname is valid.
 * A nickname is valid if it contains only alphanumeric characters and underscores.
 * 
 * @return `true` if the nickname is valid, `false` otherwise
 */
bool NickCommand::isValidNickname() {
    for (std::string::iterator it = this->_nickname.begin(); it != this->_nickname.end(); it++)
        if (!std::isalnum(*it) && *it != '_' )
            return false;
    return true;
}