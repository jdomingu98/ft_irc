#include "Channel.hpp"

/**
 * Channel name constructor.
 * 
 * @param name The name of the channel.
 */
Channel::Channel(std::string name): _name(name), _mode('n') {}

/**
 * Channel destructor.
 */
Channel::~Channel() {}

/**
 * This function aims to add a user to the channel.
 * 
 * @param user The user to add.
 * 
 * @throw `ChannelException` If the user is already in the channel.
 */
void Channel::addUser(User user) {
    std::vector<User>::iterator it = findUser(user.getNickname());
    if (it != this->_users.end())
        throw ChannelException(USER_ALREADY_IN_CHANNEL_ERR);
    this->_users.push_back(user);
}

/**
 * This function aims to remove a user from the channel.
 * 
 * @param nickname The nickname of the user to remove.
 * 
 * @throw `ChannelException` If the user is not found in the channel.
 */
void Channel::removeUser(std::string nickname) {
    std::vector<User>::iterator it = findUser(nickname);
    if (it != this->_users.end())
        this->_users.erase(it);
    else
        throw ChannelException(USER_NOT_FOUND_ERR);
}

/**
 * This function aims to find a user by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User>::iterator Channel::findUser(std::string nickname) {
    return std::find_if(this->_users.begin(), this->_users.end(), [nickname](const User& user) {
        return user.getNickname() == nickname;
    });
}

/**
 * This function aims to get the name of the channel.
 * 
 * @return The name of the channel.
 */
std::string Channel::getName() {
    return this->_name;
}

/**
 * This function aims to get the users of the channel.
 * 
 * @return The users of the channel.
 */
std::vector<User> Channel::getUsers() {
    return this->_users;
}

/**
 * This function aims to get the topic of the channel.
 * 
 * @return The topic of the channel.
 */
std::string Channel::getTopic() {
    return this->_topic;
}

/**
 * This function aims to get the mode of the channel.
 * 
 * @return The mode of the channel.
 */
char Channel::getMode() {
    return this->_mode;
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
 * This function aims to set the mode of the channel.
 * 
 * @param mode The mode of the channel.
 */
void Channel::setMode(char mode) {
    this->_mode = mode;
}