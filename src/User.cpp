#include "User.hpp"

/**
 * User file descriptor constructor
 * 
 * @param fd The file descriptor of the user
 */
User::User(int fd) : _fd(fd), _registered(false) {}

/**
 * User copy constructor
 * 
 * @param other The other user to copy.
 */
User::User(const User &other) {
    *this = other;
}

/**
 * User destructor 
 */
User::~User() {}

/**
 * This function aims to assign a user to another.
 * 
 * @param other The other user to assign.
 * 
 * @return The user assigned.
 */
User &User::operator=(const User &other) {
    if (this != &other) {
        _fd = other.getFd();
        _registered = other.isRegistered();
        _username = other.getUsername();
        _hostname = other.getHostname();
        _serverName = other._serverName;
        _realName = other._realName;
        _nickname = other.getNickname();
        _password = other._password;
        _channels.clear();
        for (size_t i = 0; i < other._channels.size(); i++)
            _channels.push_back(other._channels[i]);
    }
    return *this;
}

/**
 * This function aims to compare two users.
 * 
 * @param other The other user to compare.
 * 
 * @return `true` if the users are the same, `false` otherwise.
 */
bool User::operator<(const User& other) const {
    return _nickname < other.getNickname();
}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The const iterator to the channel with the name.
 */
std::vector<Channel *>::const_iterator User::findChannel(const std::string &channelName) const {
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == channelName)
            return _channels.begin() + i;
    }
    return _channels.end();
}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The iterator to the channel with the name.
 */
std::vector<Channel *>::iterator User::findChannel(const std::string &channelName) {
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == channelName)
            return _channels.begin() + i;
    }
    return _channels.end();
}

/**
 * This function aims to check if the user is already in the maximum number of channels.
 * 
 * @return `true` if the user is already in the maximum number of channels, `false` otherwise.
 */
bool User::isUserInMaxChannels() const {
    return _channels.size() >= MAX_CHANNELS;
}

/**
 * This function aims to check if the user is on a channel.
 * 
 * @param channelName The name of the channel.
 * 
 * @return `true` if the user is on the channel, `false` otherwise.
 */
bool User::isOnChannel(const std::string &channelName) const {
    std::vector<Channel *>::const_iterator it = findChannel(channelName);
    return it != _channels.end();
}

/**
 * This function aims to get the file descriptor of the user.
 * 
 * @return The file descriptor of the user.
 */
int User::getFd() const {
    return _fd;
}

/**
 * This function aims to get the username of the user.
 * 
 * @return The username of the user.
 */
std::string User::getUsername() const {
    return _username;
}

/**
 * This function aims to set the username of the user.
 *
 * @param username The username of the user.
 */
void User::setUsername(const std::string& username) {
    _username = username;
}

/**
 * This function aims to get the hostname of the user.
 * 
 * @return The hostname of the user.
 */
std::string User::getHostname() const {
    return _hostname;
}

/**
 * This function aims to get the real name of the user.
 * 
 * @return The real name of the user.
 */
std::string User::getRealName() const {
    return _realName;
}

/**
 * This function aims to set the hostname of the user.
 * 
 * @param hostname The hostname of the user.
 */
void User::setHostname(const std::string& hostname) {
    _hostname = hostname;
}

/**
 * This function aims to set the server name of the user.
 * 
 * @param serverName The server name of the user.
 */
void User::setServerName(const std::string& serverName) {
    _serverName = serverName;
}

/**
 * This function aims to set the real name of the user.
 *
 * @param realName The real name of the user.
 */
void User::setRealName(const std::string& realName) {
    _realName = realName;
}

/**
 * This function aims to get the nickname of the user.
 * 
 * @return The nickname of the user.
 */
std::string User::getNickname() const {
    return _nickname;
}

/**
 * This function aims to set the nickname of the user.
 * 
 * @param nickname The nickname of the user.
 */
void User::setNickname(const std::string& nickname) {
    _nickname = nickname;
}

/**
 * This function aims to set the password of the user.
 * 
 * @param password The password the user wants to use.
 */
void User::setPassword(const std::string& password) {
    _password = password;
}


/**
 * This function aims to check if the user can register.
 * 
 * @return `true` if the user can register, `false` otherwise.
 */
bool User::canRegister() const {
    return  !(_username.empty()
            || _hostname.empty()
            || _serverName.empty()
            || _realName.empty()
            || _nickname.empty());
}

/**
 * This function try to register the user and verify that it is the same password as on the server.
 * 
 */
void User::makeRegistration() {
    Server &server = Server::getInstance();

    if (!server.isValidPassword(_password))
        throw PasswordMismatchException();

    server.sendMessage(getFd(), WelcomeResponse(_nickname, _username, _hostname).getReply());
    server.sendMessage(getFd(), YourHostResponse(_nickname, _serverName).getReply());
    server.sendMessage(getFd(), CreatedResponse(_nickname, server.getCreationDate()).getReply());
    server.sendMessage(getFd(), MyInfoResponse(_nickname, _serverName).getReply());

    _registered = true;
}

/**
 * This function aims to check if the user has registered.
 * 
 * @return `true` if the user has registered, `false` otherwise.
 */
bool User::isRegistered() const {
    return _registered;
}

/**
 * This function aims to add a channel to the user.
 * 
 * @param channel The channel to be added.
 */
void User::addChannel(Channel *channel) {
    _channels.push_back(channel);
}

/**
 * This function aims to remove a channel from the user.
 * 
 * @param channelName The name of the channel to be removed.
 */
void User::removeChannel(const std::string &channelName) {
    std::vector<Channel *>::iterator channel = findChannel(channelName);
    if (channel != _channels.end())
        _channels.erase(channel);
}

/**
 * This function aims to send a private message to an user.
 * 
 * @param destination The user who will receive the message.
 * @param message The message to send.
 */
void User::sendPrivateMessageToUser(const User &destination, const std::string& message) const {
    Logger::debug("Sending private message to " + destination.getNickname() + " from " + getNickname() + ": " + message);
    std::string response = CMD_MSG(_nickname, _username, _hostname, PRIVMSG_MSG(destination.getNickname(), message));
    Server::getInstance().sendMessage(destination.getFd(), response);
}

/**
 * This function aims to send a notice message to an user.
 * 
 * @param destination The user who will receive the notice message.
 * @param message The message to send.
 */
void User::sendNoticeToUser(const User &destination, const std::string& message) const {
    Logger::debug("Sending NOTICE to " + destination.getNickname() + " from " + getNickname() + ": " + message);
    std::string response = CMD_MSG(_nickname, _username, _hostname, NOTICE_MSG(destination.getNickname(), message));
    Server::getInstance().sendMessage(destination.getFd(), response);
}

/**
 * This function aims to get a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return A pointer of the found channel or `NULL` in other case.
 */
Channel *User::getChannelByName(std::string &channelName) {
    std::vector<Channel *>::iterator it = findChannel(channelName);
    return (it != _channels.end()) ? *it : NULL;
}

/**
 * This function aims to send a private message to a channel.
 * 
 * @param destination The channel that will receive the message.
 * @param message The message to send.
 */
void User::sendPrivateMessageToChannel(const Channel &destination, const std::string& message) const {
    Logger::debug("Sending private message to channel " + destination.getName() + " from " + getNickname() + ": " + message);
    std::string response = CMD_MSG(_nickname, _username, _hostname, PRIVMSG_MSG(destination.getName(), message));
    std::vector<User *> users = destination.getUsers();
    for (size_t i = 0; i < users.size(); i++)
        if (users[i]->getNickname() != _nickname)
            Server::getInstance().sendMessage(users[i]->getFd(), response);
}

/**
 * This function aims to send a notice message to a channel.
 * 
 * @param destination The channel that will receive the message.
 * @param message The message to send.
 */
void User::sendNoticeToChannel(const Channel &destination, const std::string& message) const {
    Logger::debug("Sending private message to channel " + destination.getName() + " from " + getNickname() + ": " + message);
    std::string response = CMD_MSG(_nickname, _username, _hostname, NOTICE_MSG(destination.getName(), message));
    std::vector<User *> users = destination.getUsers();
    for (size_t i = 0; i < users.size(); i++)
        if (users[i]->getNickname() != _nickname)
            Server::getInstance().sendMessage(users[i]->getFd(), response);
}

/**
 * This function aims to get the channels of the user.
 * 
 * @return The channels of the user.
 */
std::vector<Channel *> User::getChannels() const {
    return _channels;
}