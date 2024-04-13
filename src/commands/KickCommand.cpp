#include "KickCommand.hpp"

/**
 * Construct a new KickCommand.
 * 
 * @param channels The channels to kick the users from
 * @param users The users to kick
 * @param comment The comment for the kick
 */
KickCommand::KickCommand(std::vector<Channel> &channels, const std::vector<User> &users, const std::string &comment) : ACommand(true), _channels(channels), _users(users), _comment(comment) {}

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
    std::string channelName;
    std::string kickedUser;
    for (size_t i = 0; i < _channels.size(); i++) {
        channelName = _channels[i].getName();
        kickedUser = _users[i].getNickname();
        
        if (!_channels[i].isUserInChannel(nickname))
            throw NotOnChannelException(channelName);
        
        if (!_channels[i].isOper(nickname))
            throw ChanOPrivsNeededException(channelName);
        
        if (!_channels[i].isUserInChannel(kickedUser))
            throw UserNotInChannelException(kickedUser, channelName);
        
        std::vector<User> &channelUsers = _channels[i].getAllUsers();
        std::string comment = _comment.empty() ? nickname : _comment;
        for (size_t i = 0; i < channelUsers.size(); i++) {
            Logger::debug("Sending KICK message of user " + kickedUser + ", from user " + nickname +
                            ", to user " + channelUsers[i].getNickname().c_str());
            server.sendMessage(channelUsers[i].getFd(),
                                KICK_MSG(nickname, user.getUsername(), user.getHostname(),
                                        channelName, kickedUser, comment));
        }
        channelUsers.clear();
        Logger::debug("<--- PRE REMOVE --->");
        Logger::debug("OPERATORS:");
        std::vector<User> opers = _channels[i].getOperators();
        for (size_t i = 0; i < opers.size(); i++) {
            Logger::debug(opers[i].getNickname());
        }

        Logger::debug("USERS:");
        std::vector<User> users = _channels[i].getUsers();
        for (size_t i = 0; i < users.size(); i++) {
            Logger::debug(users[i].getNickname());
        }
        _channels[i].removeUser(kickedUser);
        Logger::debug("<--- POST REMOVE --->");
        Logger::debug("OPERATORS:");
        opers = _channels[i].getOperators();
        for (size_t i = 0; i < opers.size(); i++) {
            Logger::debug(opers[i].getNickname());
        }
        
        Logger::debug("USERS:");
        users = _channels[i].getUsers();
        for (size_t i = 0; i < users.size(); i++) {
            Logger::debug(users[i].getNickname());
        }
    }
}