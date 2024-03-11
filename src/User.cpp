#include "User.hpp"

User::User(int fd): _fd(fd), _passwordChecked(false) {}

void User::checkPassword() {
    this->_passwordChecked = true;
}

bool User::isPasswordChecked() const {
    return this->_passwordChecked;
}

int User::getFd() const {
    return this->_fd;
}

void User::setUsername(const std::string& username) {
    this->_username = username;
}

void User::setHostname(const std::string& hostname) {
    this->_hostname = hostname;
}

void User::setServerName(const std::string& serverName) {
    this->_serverName = serverName;
}

void User::setRealName(const std::string& realName) {
    this->_realName = realName;
}
