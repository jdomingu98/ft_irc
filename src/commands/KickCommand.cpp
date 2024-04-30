#include "KickCommand.hpp"

/**
 * Construct a new KickCommand.
 * 
 * @param channels The channels to kick the users from
 * @param users The users to kick
 * @param comment The comment for the kick
 */
KickCommand::KickCommand(const std::vector<std::string> &channels, const std::vector<User> &users, const std::string &comment)
    : ACommand(true), _channels(channels), _users(users), _comment(comment) {}

/**
 * Destroys the KickCommand.
 */
KickCommand::~KickCommand() {}

/**
 * Executes the command KICK.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NotOnChannelException` If the user is not on the channel
 * @throws `ChanOPrivsNeededException` If the user is not an operator of the channel
 * @throws `NoSuchChannelException` If the channel does not exist
 */
void KickCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);

    const std::string &nickname = user.getNickname();
    const std::string &comment = this->_comment.empty() ? nickname : this->_comment;

    for (size_t i = 0; i < this->_channels.size(); i++) {
        try {
            Channel &channel = server.getChannelByName(this->_channels[i]);
        
            if (!channel.isUserInChannel(nickname))
                throw NotOnChannelException(this->_channels[i]);

            if (!channel.isOper(nickname))
                throw ChanOPrivsNeededException(this->_channels[i]);

            size_t pos = this->_channels.size() == this->_users.size() ? i : 0;
            std::string kickedUser = this->_users[pos].getNickname();
            if (this->_channels.size() == 1) {
                for (size_t j = 0; j < this->_users.size(); j++) {
                    kickedUser = this->_users[j].getNickname();
                    kickUserFromChannel(channel, user, kickedUser, comment);
                }
                continue;
            }
            kickUserFromChannel(channel, user, kickedUser, comment);
        } catch (NoSuchChannelException &e) {
            Logger::debug("Channel " + this->_channels[i] + " does not exist.");
            server.sendExceptionMessage(clientFd, e);
        }
    }
}

/**
 * Kicks a user from a channel.
 * 
 * @param channel The channel to kick the user from
 * @param user The user that is kicking
 * @param kickedUser The user to kick
 * @param comment The comment for the kick
 * 
 * @throws `UserNotInChannelException` If the user is not in the channel
*/
void KickCommand::kickUserFromChannel(Channel &channel, const User &user,
                                        const std::string &kickedUser, const std::string &comment) {
    if (!channel.isUserInChannel(kickedUser))
        throw UserNotInChannelException(kickedUser, channel.getName(), Server::getInstance().sendMessage);

    user.broadcastToChannel(channel.getAllUsers(), KICK_MSG(channel.getName(), kickedUser, comment));
    channel.removeUser(kickedUser);
}