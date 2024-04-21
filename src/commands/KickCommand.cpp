#include "KickCommand.hpp"

/**
 * Construct a new KickCommand.
 * 
 * @param channels The channels to kick the users from
 * @param users The users to kick
 * @param comment The comment for the kick
 */
KickCommand::KickCommand(const std::vector<std::string> &channels, const std::vector<User> &users, std::string comment)
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
 */
void KickCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);

    std::string nickname = user.getNickname();
    std::string comment = this->_comment.empty() ? nickname : this->_comment;
    std::string kickedUser;

    for (size_t i = 0; i < this->_channels.size(); i++) {
        Channel &channel = server.getChannelByName(this->_channels[i]);

        if (!channel.isUserInChannel(nickname))
            throw NotOnChannelException(this->_channels[i]);

        if (!channel.isOper(nickname))
            throw ChanOPrivsNeededException(this->_channels[i]);

        kickedUser = this->_channels.size() == this->_users.size()  ? this->_users[i].getNickname()
                                                                    : this->_users[0].getNickname();
        if (this->_channels.size() == 1 && this->_users.size() > 1) {
            for (size_t j = 0; j < this->_users.size(); j++) {
                kickedUser = this->_users[j].getNickname();
                kickUserFromChannel(channel, nickname, kickedUser, comment);
            }
            continue;
        }
        kickUserFromChannel(channel, nickname, kickedUser, comment);
    }
}

void KickCommand::kickUserFromChannel(const Channel &channel, const std::string &nickname,
                                        const std::string &kickedUser, const std::string &comment) {
    Server &server = Server::getInstance();

    if (!channel.isUserInChannel(kickedUser))
        throw UserNotInChannelException(kickedUser, channel.getName());

    std::vector<User> channelUsers = channel.getAllUsers();

    for (size_t j = 0; j < channelUsers.size(); j++) {
        Logger::debug("Sending KICK message of user " + kickedUser + " to user " + channelUsers[j].getNickname().c_str());
        server.sendMessage(channelUsers[j].getFd(),
                            KICK_MSG(nickname, user.getUsername(), user.getHostname(),
                                    channel.getName(), kickedUser, comment));
    }
    channelUsers.clear();
    channel.removeUser(kickedUser);
}