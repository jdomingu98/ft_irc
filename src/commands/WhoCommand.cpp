#include "WhoCommand.hpp"

/**
 * Command WHO default constructor
 * 
 */
WhoCommand::WhoCommand() : ACommand(true), _query(NONE), _hasOperatorFlag(false) {}

/**
 * Command WHO constructor
 * 
 * @param query The query to search for
 * @param hasOperatorFlag Whether to only show operator users
 */
WhoCommand::WhoCommand(const std::string &query, const bool hasOperatorFlag)
    : ACommand(true), _query(query), _hasOperatorFlag(hasOperatorFlag) {}

/**
 * Gets the result of the WHO command for a channel given
 * 
 * @param clientFd The socket file descriptor of the client
 * @param channel The channel to get the query of
 */
void WhoCommand::getQueryOfChannel(int clientFd, const Channel &channel) {
    const std::vector<User *> &users = channel.getAllUsers();
    std::vector<User *>::const_iterator it;

    for (it = users.begin(); it != users.end(); ++it) {
        const std::string &nick = (*it)->getNickname();
        const bool isOper = channel.isOper(nick);
        
        if (_hasOperatorFlag && !isOper)
            continue;
        
        Server::getInstance().sendMessage(clientFd,
            WhoReplyResponse(_query, (*it)->getUsername(), (*it)->getHostname(),
                nick, isOper ? "@" : NONE, (*it)->getRealName()
            ).getReply()
        );
    }
}

/**
 * Executes the command WHO
 * 
 * @param clientFd The socket file descriptor of the client
 */
void WhoCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    try { // If the query is a channel
        const Channel &channel = server.getChannelByName(_query);
        getQueryOfChannel(clientFd, channel);
    } catch (NoSuchChannelException &e) {
        try { // The query is an user
            const User *user = server.getUserByNickname(_query);

            const std::vector<Channel *> channels = user->getChannels();
            std::vector<Channel *>::const_iterator channelIt;
            for (channelIt = channels.begin(); channelIt != channels.end(); ++channelIt)
                getQueryOfChannel(clientFd, **channelIt);
        } catch (NoSuchNickException &e) {
            // The query is not a channel nor an user (nickname)
            const std::vector<User *> usersServer = server.getUsers();
            std::vector<User *>::const_iterator usersIt;
            for (usersIt = usersServer.begin(); usersIt != usersServer.end(); ++usersIt) {
                if ((*usersIt)->getUsername() != _query &&
                    (*usersIt)->getHostname() != _query &&
                    (*usersIt)->getRealName() != _query)
                    continue;
                const std::vector<Channel *> channels = (*usersIt)->getChannels();
                std::vector<Channel *>::const_iterator channelIt2;
                for (channelIt2 = channels.begin(); channelIt2 != channels.end(); ++channelIt2)
                    getQueryOfChannel(clientFd, **channelIt2);
            }
            // None of the above matched, so we will show all users if query is NONE
            if (_query == NONE) {
                const std::vector<Channel> &channels = server.getChannels();
                std::vector<Channel>::const_iterator it;
                for (it = channels.begin(); it != channels.end(); ++it)
                    getQueryOfChannel(clientFd, *it);
            }
        }
    }
    server.sendMessage(clientFd, EndOfWhoResponse(_query).getReply());
}