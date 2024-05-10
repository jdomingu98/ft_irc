#include "KickCommand.hpp"

/**
 * Construct a new KickCommand.
 * 
 * @param channels The channels to kick the users from
 * @param users The users to kick
 * @param comment The comment for the kick
 */
KickCommand::KickCommand(const std::vector<std::string> &channels, const std::vector<std::string> &users, const std::string &comment)
    : ACommand(true), _channels(channels), _users(users), _comment(comment) {}

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

    if (_channels.size() != _users.size() && _channels.size() != 1 && _users.size() != 1)
        throw NeedMoreParamsException(KICK);

    Server &server = Server::getInstance();
    const User *me = server.getUserByFd(clientFd);

    const std::string &nickname = me->getNickname();
    const std::string comment = _comment.empty() ? nickname : _comment;

    for (size_t i = 0; i < _channels.size(); ++i) {
        try {
            Channel *channel = server.getChannelByName(_channels[i]);

            if (!me->isOnChannel(_channels[i]))
                throw NotOnChannelException(_channels[i]);

            if (!channel->isOper(nickname))
                throw ChanOPrivsNeededException(_channels[i]);

            //std::vector<User *> users = initializeUsers(clientFd);
            if (_channels.size() == 1) {
                std::vector<std::string>::const_iterator userIt;
                for (userIt = _users.begin(); userIt != _users.end(); ++userIt)
                    kickUserFromChannel(*channel, *me, *userIt, comment);
            } else {
                const size_t pos = _channels.size() == _users.size() ? i : 0;
                kickUserFromChannel(*channel, *me, _users[pos], comment);
            }
        } catch (const NoSuchChannelException &e) {
            Logger::debug("Channel " + _channels[i] + " does not exist.");
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
void KickCommand::kickUserFromChannel(Channel &channel, const User &me, const std::string &kickedUser, const std::string &comment) {
    Server &server = Server::getInstance();
    
    try {
        User *kicked = server.getUserByNickname(kickedUser);
        if (!kicked->isOnChannel(channel.getName()))
            throw NotOnChannelException(channel.getName());

        const std::vector<User *> allUsers = channel.getUsers();
        for (std::vector<User *>::const_iterator it = allUsers.begin(); it != allUsers.end(); ++it) {
            Logger::debug("Sending KICK message of user " + kickedUser + " to user " + (*it)->getNickname().c_str());
            server.sendMessage((*it)->getFd(),
                                CMD_MSG(me.getNickname(), me.getUsername(), me.getHostname(),
                                    KICK_MSG(channel.getName(), kickedUser, comment)
                                )
                            );
        }  
    channel.removeUser(kickedUser);
    } catch (const IRCException& e) {
        Logger::debug("User not found!. Continue parsing KICK command.");
        server.sendExceptionMessage(me.getFd(), e);
    }
}