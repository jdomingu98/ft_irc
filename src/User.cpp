#include "User.hpp"

/**
 * User file descriptor constructor
 * 
 * @param fd The file descriptor of the user
 */
User::User(int fd): _fd(fd), _passwordChecked(false) {}

/**
 * User destructor 
 */
User::~User() {}

/**
 * This function aims to check the password of the user, setting is as `true`.
 */
void User::checkPassword() {
    this->_passwordChecked = true;
}

/**
 * This function aims to check if the password is already checked.
 */
bool User::isPasswordChecked() const {
    return this->_passwordChecked;
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
 */
void User::setUsername(const std::string& username) {
    this->_username = username;
}

/**
 * This function aims to get the hostname of the user.
 * 
 */
void User::setHostname(const std::string& hostname) {
    this->_hostname = hostname;
}

/**
 * This function aims to get the server name of the user.
 * 
 */
void User::setServerName(const std::string& serverName) {
    this->_serverName = serverName;
}

/**
 * This function aims to get the real name of the user.
 *
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
 */
void User::setNickname(const std::string& nickname){
    this->_nickname = nickname;
}
