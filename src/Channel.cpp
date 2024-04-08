#include "Channel.hpp"

/**
 * Channel name and User constructor.
 * 
 * @param name The name of the channel.
 * 
 * @throws `BadChannelMaskException` If the channel name is invalid.
 */
Channel::Channel(const std::string &name, const User &user)
    : _password(NONE), _topic(NONE), _limit(NO_LIMIT), _passwordSet(false), _inviteOnly(false) {
    if (!checkChannelName(name))
        throw BadChannelMaskException(name);
    this->_name = name;
    this->_operators.push_back(user);
}

/**
 * Channel destructor.
 */
Channel::~Channel() {
    this->_users.clear();
    this->_operators.clear();
}

/**
 * This function aims to check if the channel name is valid.
 * 
 * @param name The name of the channel.
 * 
 * @return `true` if the channel name is valid, `false` otherwise.
 */
bool Channel::checkChannelName(std::string name) const {
    if ((name[0] != '#' && name[0] != '&') || name.size() > MAX_CHANNEL_NAME_LENGTH)
            return false;
    for (size_t i = 1; i < name.size(); i++) {
        if (name[i] == ' ' || name[i] == ',' || name[i] == BELL_CHAR)
            return false;
    }
    return true;
}

/**
 * This function aims to find a user by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User>::iterator Channel::findUser(const std::string &nickname) {
    for (size_t i = 0; i < this->_users.size(); i++) {
        if (this->_users[i].getNickname() == nickname)
            return this->_users.begin() + i;
    }
    return this->_users.end();
}

/**
 * This function aims to find a user by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User>::const_iterator Channel::findUser(const std::string &nickname) const {
    for (size_t i = 0; i < this->_users.size(); i++) {
        if (this->_users[i].getNickname() == nickname)
            return this->_users.begin() + i;
    }
    return this->_users.end();
}

/**
 * This function aims to find a oper by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User>::iterator Channel::findOper(const std::string &nickname) {
    for (size_t i = 0; i < this->_operators.size(); i++) {
        if (this->_operators[i].getNickname() == nickname)
            return this->_operators.begin() + i;
    }
    return this->_operators.end();
}

/**
 * This function aims to find a oper by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User>::const_iterator Channel::findOper(const std::string &nickname) const {
    for (size_t i = 0; i < this->_operators.size(); i++) {
        if (this->_operators[i].getNickname() == nickname)
            return this->_operators.begin() + i;
    }
    return this->_operators.end();
}

/**
 * This function aims to get the name of the channel.
 * 
 * @return The name of the channel.
 */
std::string Channel::getName() const {
    return this->_name;
}

/**
 * This function aims to get the password of the channel.
 * 
 * @return The password of the channel.
 */
std::string Channel::getPassword() const {
    return this->_password;
}

/**
 * This function aims to get the users of the channel.
 * 
 * @return The users of the channel.
 */
std::vector<User> Channel::getUsers() const {
    return this->_users;
}

/**
 * This function aims to get the operators of the channel.
 * 
 * @return The operators of the channel.
 */
std::vector<User> Channel::getOperators() const {
    return this->_operators;
}

/**
 * This function aims to get all the users of the channel.
 * 
 * @return All the users of the channel.
 */
std::vector<User> Channel::getAllUsers() const {
    std::vector<User> allUsers = this->_operators;
    allUsers.insert(allUsers.end(), this->_users.begin(), this->_users.end());
    return allUsers;
}

/**
 * This function aims to get the topic of the channel.
 * 
 * @return The topic of the channel.
 */
std::string Channel::getTopic() const {
    return this->_topic;
}

/**
 * This function aims to get if the password is set.
 * 
 * @return `true` if the password is set, `false` otherwise.
 */
bool Channel::isPasswordSet() const {
    return this->_passwordSet;
}

/**
 * This function aims to set the password of the channel.
 * 
 * @param password The password of the channel.
 * 
 */
void Channel::setPassword(const std::string &password) {
    this->_password = password;
    this->_passwordSet = true;
}

/**
 * This function aims to unset the password of the channel.
*/
void Channel::unsetPassword() {
    this->_password = "";
    this->_passwordSet = false;
}

/**
 * This function aims to set the topic of the channel.
 * 
 * @param topic The topic of the channel.
 */
void Channel::setTopic(std::string topic) {
    this->_topic = topic;
}

/**
 * This function aims to set the password of the channel.
 * 
 * @param password The password of the channel.
 * 
 * @return `true` if the password provided matchs the channel password, `false` otherwise.
 * */
bool Channel::checkPassword(std::string password) const {
    return this->_password == password;
}

/**
 * This function aims to check if the user is invited to the channel.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return `true` if the user is invited, `false` otherwise.
 */
bool Channel::isUserInvited(std::string nickname) const {
    return std::find(this->_inviteList.begin(), this->_inviteList.end(), nickname) != this->_inviteList.end();
}

/**
 * This function aims to invite a user to the channel.
 * 
 * @param nickname The nickname of the user.
 * 
 * @throw `ChannelException` If the user is already invited.
 * 
 */
void Channel::inviteUser(const std::string &nickname) {
    if (!isUserInvited(nickname))
        this->_inviteList.push_back(nickname);
}

/**
 * This function aims to set the limit of users in the channel.
 * 
 * @param limit The limit of users.
 * 
 */
void Channel::setLimit(int limit) {
    this->_limit = limit;
}

/**
 * This function aims to check if the channel has a limit of users.
 * 
 * @return `true` if the channel has a limit of users, `false` otherwise.
 */
bool Channel::hasLimit() const {
    return this->_limit != NO_LIMIT;
}

/**
 * This function aims to check if the channel is full.
 * 
 * @return `true` if the channel is full, `false` otherwise.
 */
bool Channel::isFull() const {
    return (int) (this->_users.size() + this->_operators.size()) == this->_limit;
}

/**
 * This function aims to add a user to the channel.
 * 
 * @param user The user to add.
 * 
 * @throw `ChannelException` If the user is already in the channel.
 */
void Channel::addUser(User user) {
    std::vector<User>::iterator it = findUser(user.getNickname());
    if (it != this->_users.end()) {}
        //throw ChannelException(USER_ALREADY_IN_CHANNEL_ERR);
    this->_users.push_back(user);
}

/**
 * This function aims to add an operator to the channel.
 * 
 * @param user The operator to add.
 * 
 * @throw `ChannelException` If the operator is already in the channel.
 */
void Channel::addOper(User user) {
    std::vector<User>::iterator it = findOper(user.getNickname());
    if (it != this->_operators.end()) {}
        //throw ChannelException(USER_ALREADY_IN_CHANNEL_ERR);
    this->_operators.push_back(user);
}

/**
 * This function aims to remove a user from the channel.
 * 
 * @param nickname The nickname of the user to remove.
 * 
 * @throw `UserNotInChannelException` If the user is not found in the channel.
 */
void Channel::removeUser(std::string nickname) {
    Server& server = Server::getInstance();
    std::vector<User>::iterator itUser = findUser(nickname);
    std::vector<User>::iterator itOper = findOper(nickname);
    if (itUser != this->_users.end())
        this->_users.erase(itUser);
    else if (itOper != this->_operators.end())
        this->_operators.erase(itOper);
    else
        throw UserNotInChannelException(nickname, this->_name);
    if (this->_users.empty() && this->_operators.empty()) {
        server.getChannels().erase(server.findChannel(this->_name));
        this->~Channel();
    }
}

/**
 * This function tells if a user is in the channel.
 * 
 * @param nickname The nickname of the user to check.
 * 
 * @return `true` if the user is in the channel, `false` otherwise.
 */
bool Channel::isUserInChannel(const std::string &nickname) const {
    return findOper(nickname) != this->_operators.end() || findUser(nickname) != this->_users.end();
}

/**
 * This function aims to make a user an operator of the channel.
 * 
 * @param nickname The nickname of the user to make an operator.
 * 
 * @throw `UserNotInChannelException` If the user is not found in the channel.
 */
void Channel::makeUserAnOper(std::string nickname) {
    std::vector<User>::iterator it = findUser(nickname);
    if (it != this->_users.end()) {
        this->_operators.push_back(*it);
        this->_users.erase(it);
    } else
        throw UserNotInChannelException(nickname, this->_name);
}

/**
 * This function aims to make an operator a user of the channel.
 * 
 * @param nickname The nickname of the operator to make a user.
 * 
 * @throw `UserNotInChannelException` If the operator is not found in the channel.
 */
void Channel::makeOperAnUser(std::string nickname) {
    std::vector<User>::iterator it = findOper(nickname);
    if (it != this->_operators.end()) {
        it->setNickname(it->getNickname().substr(1));
        this->_users.push_back(*it);
        this->_operators.erase(it);
    } else
        throw UserNotInChannelException(nickname, this->_name);
}

/**
 * This function aims to check if a user is an operator of the channel.
 * 
 * @param nickname The nickname of the user to check.
 * 
 * @return `true` if the user is an operator, `false` otherwise.
 */
bool Channel::isOper(const std::string &nickname) const {
    return findOper(nickname) != this->_operators.end();
}

/**
 * This function aims to check if the channel is invite-only.
 * 
 * @return `true` if the channel is invite-only, `false` otherwise.
 */
bool Channel::isInviteOnly() const {
    return this->_inviteOnly;
}

/**
 * This function aims to set the channel as invite-only.
 */
void Channel::setInviteOnly(bool inviteOnly) {
    this->_inviteOnly = inviteOnly;
}

/**
 * This function aims to check if the channel is topic-protected.
 * 
 * @return `true` if the channel is topic-protected, `false` otherwise.
 */
bool Channel::isTopicProtected() const {
    return this->_topicProtected;
}

/**
 * This function aims to set the channel as topic-protected.
 */
void Channel::setTopicProtected(bool topicProtected) {
    this->_topicProtected = topicProtected;
}

/**
 * This function aims to broadcast a message to the channel.
 * 
 * @param message The message to broadcast.
 * @param nickname The nickname of the user who sends the message.
 */
void Channel::broadcastToChannel(const std::string &message, const std::string &nickname) {
    Server& server = Server::getInstance();
    std::vector<User> allUsers = getAllUsers();
    for (size_t i = 0; i < allUsers.size(); i++) {
        if (allUsers[i].getNickname() != nickname)
            server.sendMessage(allUsers[i].getFd(), message);
    }
}