#include "User.hpp"

/**
 * User file descriptor constructor
 * 
 * @param fd The file descriptor of the user
 */
User::User(int fd) : _fd(fd), _passwordChecked(false) {}

/**
 * User destructor 
 */
User::~User() {}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The const iterator to the channel with the name.
 */
std::vector<Channel>::const_iterator User::findChannel(std::string channelName) const {
    for (size_t i = 0; i < this->_channels.size(); i++) {
        if (this->_channels[i].getName() == channelName)
            return this->_channels.begin() + i;
    }
    return this->_channels.end();
}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The iterator to the channel with the name.
 */
std::vector<Channel>::iterator User::findChannel(std::string channelName) {
    for (size_t i = 0; i < this->_channels.size(); i++) {
        if (this->_channels[i].getName() == channelName)
            return this->_channels.begin() + i;
    }
    return this->_channels.end();
}

/**
 * This function aims to check the password of the user, setting is as `true`.
 */
void User::checkPassword() {
    this->_passwordChecked = true;
}

/**
 * This function aims to check if the password is already checked.
 * 
 * @return `true` if the password is already checked, `false` otherwise.
 */
bool User::isPasswordChecked() const {
    return this->_passwordChecked;
}

/**
 * This function aims to check if the user is already in the maximum number of channels.
 * 
 * @return `true` if the user is already in the maximum number of channels, `false` otherwise.
 */
bool User::isUserInMaxChannels() const {
    return this->_channels.size() >= MAX_CHANNELS;
}

/**
 * This function aims to check if the user is already in a channel.
 * 
 * @param channelName The name of the channel.
 * 
 * @return `true` if the user is already in the channel, `false` otherwise.
 */
bool User::isAlreadyInChannel(std::string channelName) const {
    
    std::vector<Channel>::const_iterator it = findChannel(channelName);
    return it != this->_channels.end();
}

/**
 * This function aims to get the file descriptor of the user.
 * 
 * @return The file descriptor of the user.
 */
int User::getFd() const {
    return this->_fd;
}

/**
 * This function aims to get the username of the user.
 * 
 * @return The username of the user.
 */
std::string User::getUsername() const {
    return this->_username;
}

/**
 * This function aims to set the username of the user.
 *
 * @param username The username of the user.
 */
void User::setUsername(const std::string& username) {
    this->_username = username;
}

/**
 * This function aims to set the hostname of the user.
 * 
 * @param hostname The hostname of the user.
 */
void User::setHostname(const std::string& hostname) {
    this->_hostname = hostname;
}

/**
 * This function aims to set the server name of the user.
 * 
 * @param serverName The server name of the user.
 */
void User::setServerName(const std::string& serverName) {
    this->_serverName = serverName;
}

/**
 * This function aims to set the real name of the user.
 *
 * @param realName The real name of the user.
 */
void User::setRealName(const std::string& realName) {
    this->_realName = realName;
}

/**
 * This function aims to get the nickname of the user.
 * 
 * @return The nickname of the user.
 */
std::string User::getNickname() const {
    return this->_nickname;
}

/**
 * This function aims to set the nickname of the user.
 * 
 * @param nickname The nickname of the user.
 */
void User::setNickname(const std::string& nickname) {
    this->_nickname = nickname;
}

/**
 * This function aims to set the password of the user.
 * 
 * @param password The password the user wants to use.
 */
void User::setPassword(const std::string& password) {
    this->_password = password;
}

/**
 * This function aims to check if the user can register.
 * 
 * @return `true` if the user can register, `false` otherwise.
 */
bool User::canRegister() {
    return !(this->_username.empty() || this->_hostname.empty() ||
    this->_serverName.empty() || this->_realName.empty() || this->_nickname.empty());
}

/**
 * This function try to register the user and verify that it is the same password as on the server.
 * 
 * @param server The server where the user is trying to register.
 */
void User::makeRegistration(Server &server) {
    if (!server.isValidPassword(_password))
        throw PasswordMismatchException();
    this->_registered = true;   
}

/**
 * This function aims to check if the user has registered.
 * 
 * @return `true` if the user has registered, `false` otherwise.
 */
bool User::isRegistered() const {
    return this->_registered;
}

/**
 * This function aims to join a channel.
 * 
 * @param channel The channel to join.
 */
void User::joinChannel(Channel channel) {
    if (isUserInMaxChannels())
        //throw UserException(USER_CHANNEL_FULL_ERR);
    if (isAlreadyInChannel(channel.getName()))
        //throw UserException(USER_ALREADY_IN_CHANNEL_ERR);
    // Comprobar que el canal es de solo invitación y puede entrar
    // Comprobar que el canal tiene contraseña y la contraseña es correcta
    // Comprobar que el canal tiene límite y no se ha alcanzado
    this->_channels.push_back(channel);
}

/**
 * This function aims to leave a channel.
 * 
 * @param channelName The name of the channel to leave.
 */
void User::leaveChannel(std::string channelName) {
    std::vector<Channel>::iterator it = findChannel(channelName);
    if (it != this->_channels.end())
        this->_channels.erase(it);
    else {}
        //throw UserException(USER_CHANNEL_NOT_FOUND_ERR);
}

/**
 * This function aims to send a private message to a user.
 * 
 * @param server The server where the user is connected.
 * @param destination The user who will receive the message.
 * @param message The message to send.
 */
void User::sendPrivateMessageToUser(const Server &server, const User &destination, const std::string& message) {
    Logger::debug("Sending private message to " + destination.getNickname() + " from " + this->getNickname() + ": " + message);
    std::string response = ":" + this->_nickname + " PRIVMSG " + destination.getNickname() + " :" + message;
    server.sendMessage(destination.getFd(), response);
}