#include "KickCommand.hpp"

/**
 * Construct a new KickCommand.
 * 
 * @param channels The channels to kick the users from
 * @param users The users to kick
 * @param comment The comment for the kick
 */
KickCommand::KickCommand(std::vector<Channel> channels, std::vector<User> users, std::string comment) : ACommand(true), _channels(channels), _users(users), _comment(comment) {}

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
            throw new NotOnChannelException(channelName);
        
        if (!_channels[i].isOper(nickname))
            throw new ChanOPrivsNeededException(channelName);
        
        if (!_channels[i].isUserInChannel(kickedUser))
            throw new UserNotInChannelException(kickedUser, channelName);

        if (nickname == kickedUser) {} //??
            //throw ...
        
        std::vector<User> channelUsers = _channels[i].getAllUsers();
        std::string comment = _comment.empty() ? nickname : _comment;
        for (size_t i = 0; i < channelUsers.size(); i++)
            server.sendMessage(channelUsers[i].getFd(), KICK_MSG(nickname,
                                                                    user.getUsername(),
                                                                    user.getHostname(),
                                                                    channelName,
                                                                    kickedUser,
                                                                    comment));
        channelUsers.clear();
        _channels[i].removeUser(kickedUser);
    }
}