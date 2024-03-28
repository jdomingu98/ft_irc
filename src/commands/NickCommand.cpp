#include "NickCommand.hpp"

/**
 * NickCommand default constructor.
 */
NickCommand::NickCommand() : ICommand(false),  _nickname("") {}

/**
 * NickCommand nickname constructor.
 * 
 * @param nickname The nickname
 */
NickCommand::NickCommand(const std::string& nickname) : ICommand(false), _nickname(nickname) {}

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
 * @throws `NickCollisionException` If the nickname is already in use and the user is not registered
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

    if (server.isNicknameInUse(this->_nickname)) {
        user.isRegistered()
            ? throw NicknameInUseException(this->_nickname)
            : throw NickCollisionException(this->_nickname);
    }

    if (!NickCommand::isValidNickname())
        throw ErroneousNicknameException(this->_nickname);

    user.setNickname(this->_nickname);
    if (user.canRegister())
        server.attemptUserRegistration(clientFd);
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