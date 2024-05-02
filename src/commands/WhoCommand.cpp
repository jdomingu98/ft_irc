#include "WhoCommand.hpp"

/**
 * Command WHO default constructor
 */
WhoCommand::WhoCommand() : _query(NONE), _hasOperatorFlag(false) {}

/**
 * Command WHO constructor
 * 
 * @param query The query to search for
 * @param hasOperatorFlag Whether to only show operator users
 */
WhoCommand::WhoCommand(const std::string query, const bool &hasOperatorFlag) : _query(query), _hasOperatorFlag(hasOperatorFlag) {}

/**
 * Destroys the WHO command
 */
WhoCommand::~WhoCommand() {}


/**
 * Gets the result of the WHO command for a channel given
 * 
 * @param clientFd The socket file descriptor of the client
 * @param channel The channel to get the query of
 */
void WhoCommand::getQueryOfChannel(const int &clientFd, Channel &channel) {
    const std::vector<User *> &users = channel.getAllUsers();
    for (size_t i = 0; i < users.size(); i++) {
        if (this->_hasOperatorFlag && !channel.isOper(users[i]->getNickname()))
            continue;
        Server::getInstance().sendMessage(clientFd,
            WhoReplyResponse(
                this->_query,
                users[i]->getUsername(),
                users[i]->getHostname(),
                users[i]->getNickname(),
                channel.isOper(users[i]->getNickname()) ? "@" : NONE,
                users[i]->getRealName()
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

    try { // If the query is a channel
        Channel &channel = server.getChannelByName(this->_query);
        getQueryOfChannel(clientFd, channel);
    } catch (NoSuchChannelException &e) {
        try { // The query is an user
            User &user = server.getUserByNickname(this->_query);
            std::vector<Channel> &channels = user.getChannels();

            for (size_t i = 0; i < channels.size(); i++)
                getQueryOfChannel(clientFd, channels[i]);
        } catch (NoSuchNickException &e) {
            // The query is not a channel nor an user
            if (this->_query == NONE) {
                std::vector<Channel> &channels = server.getChannels();
                for (size_t i = 0; i < channels.size(); i++)
                    getQueryOfChannel(clientFd, channels[i]);
            }
        }
    }
    Server::getInstance().sendMessage(clientFd, EndOfWhoResponse(this->_query).getReply());
}