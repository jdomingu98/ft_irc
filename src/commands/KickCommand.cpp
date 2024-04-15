#include "KickCommand.hpp"

/**
 * Construct a new KickCommand.
 * 
 * @param channels The channels to kick the users from
 * @param users The users to kick
 * @param comment The comment for the kick
 */
KickCommand::KickCommand(std::vector<std::string> channels, const std::vector<User> &users, std::string comment) : ACommand(true), _channels(channels), _users(users), _comment(comment) {}

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

    // Doy por hecho que _channels.size() == _users.size()
    std::string kickedUser;
    for (size_t i = 0; i < this->_channels.size(); i++) {
        kickedUser = (this->_users)[i].getNickname();

        Channel &channel = server.getChannelByName(this->_channels[i]);

        if (!channel.isUserInChannel(nickname))
            throw NotOnChannelException(this->_channels[i]);
        
        if (!channel.isOper(nickname))
            throw ChanOPrivsNeededException(this->_channels[i]);
        
        if (!channel.isUserInChannel(kickedUser))
            throw UserNotInChannelException(kickedUser, this->_channels[i]);
        
        std::vector<User> channelUsers = channel.getAllUsers();
        std::string comment = _comment.empty() ? nickname : _comment;
        for (size_t j = 0; j < channelUsers.size(); j++) {
            Logger::debug("Sending KICK message of user " + kickedUser + " to user " + channelUsers[j].getNickname().c_str());
            server.sendMessage(channelUsers[j].getFd(),
                                KICK_MSG(nickname, user.getUsername(), user.getHostname(),
                                        this->_channels[i], kickedUser, comment));
        }
        channelUsers.clear();
        channel.removeUser(kickedUser);
    }
}