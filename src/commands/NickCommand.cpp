#include "NickCommand.hpp"

/**
 * NickCommand nickname constructor.
 * 
 * @param nickname The nickname
 */
NickCommand::NickCommand(const std::string& nickname) : ACommand(false), _nickname(nickname) {}

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
    Server &server = Server::getInstance();
    if (this->_nickname.empty())
        throw NoNicknameGivenException();

    if (this->_nickname.size() > MAX_NICKNAME_SIZE || !isValidNickname())
        throw ErroneousNicknameException(this->_nickname);
    User *user = server.getUserByFd(clientFd);
    std::string nickname = user->getNickname();
    if (server.isNicknameInUse(this->_nickname) && nickname != this->_nickname)
        throw NicknameInUseException(this->_nickname);
    
    std::set<User *> users;
    const std::vector<Channel *> channels = user->getChannels();
    if (user->isRegistered() && nickname != this->_nickname) {
        users.insert(user);
        for (size_t i = 0; i < channels.size(); i++) {
            const std::vector<User *> allUsers = channels[i]->getAllUsers();
            for (size_t j = 0; j < allUsers.size(); j++)
                users.insert(allUsers[j]);
        }
        std::set<User *>::const_iterator it;
        for (it = users.begin(); it != users.end(); it++)
            server.sendMessage((*it)->getFd(), 
                        CMD_MSG(nickname, user->getUsername(), user->getHostname(),
                                NICK_MSG(this->_nickname)));
    }
    user->setNickname(this->_nickname);

    if (!user->isRegistered() && user->canRegister())
        user->makeRegistration();
}

/**
 * Check if the nickname is valid.
 * A nickname is valid if it contains only alphanumeric characters and underscores.
 * 
 * @return `true` if the nickname is valid, `false` otherwise
 */
bool NickCommand::isValidNickname() const {
    for (std::string::const_iterator it = this->_nickname.begin(); it != this->_nickname.end(); ++it)
        if (!std::isalnum(*it) && *it != '_' )
            return false;
    return true;
}