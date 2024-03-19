#include "NickCommand.hpp"

/**
 * NickCommand default constructor.
 */
NickCommand::NickCommand(): ICommand(false),  _nickname("") {}

/**
 * NickCommand nickname constructor.
 * 
 * @param nickname The nickname
 */
NickCommand::NickCommand(const std::string& nickname): ICommand(false), _nickname(nickname) {}

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
void NickCommand::execute(Server &server, int clientFd) {
    if (this->_nickname.empty())
        throw NoNicknameGivenException();

    if (this->_nickname.size() > MAX_NICKNAME_SIZE)
        throw ErroneousNicknameException(this->_nickname);

    if (server.isNicknameInUse(this->_nickname)) {
        // TODO: If user is not registered, we throw NickCollisionException
        throw NickCollisionException(this->_nickname);
        // TODO: If user is registered, we throw NicknameInUseException
        // throw NicknameInUseException(_nickname);
    }
    
    if (!NickCommand::isValidNickname())
        throw ErroneousNicknameException(this->_nickname);

    server.getUserByFd(clientFd).setNickname(this->_nickname);
    if(server.getUserByFd(clientFd).canRegister())
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