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
    User &user = server.getUserByFd(clientFd);
    if (this->_nickname.empty())
        throw NoNicknameGivenException();

    if (this->_nickname.size() > MAX_NICKNAME_SIZE)
        throw ErroneousNicknameException(this->_nickname);

    if (user.getNickname() != this->_nickname && server.isNicknameInUse(this->_nickname))
        throw NicknameInUseException(this->_nickname);

    if (!NickCommand::isValidNickname())
        throw ErroneousNicknameException(this->_nickname);
    
    std::set<User *> allUsers;
    std::vector<Channel> &channels = user.getChannels();

    if (user.isRegistered() && user.getNickname() != this->_nickname) {
        allUsers.insert(&user);
        for (size_t i = 0; i < channels.size(); i++) {
            std::vector<User *> usersChannel = channels[i].getAllUsers();
            for (size_t j = 0; j < usersChannel.size(); j++)
                allUsers.insert(usersChannel[j]);
        }
        for ( std::set<User *>::iterator it = allUsers.begin(); it != allUsers.end(); it++)
            server.sendMessage((*it)->getFd(), 
                        CMD_MSG(user.getNickname(), user.getUsername(), user.getHostname(),
                                NICK_MSG(this->_nickname)));
    }

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