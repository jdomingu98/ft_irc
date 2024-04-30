#include "WhoCommand.hpp"

/**
 * Command WHO default constructor
 * 
 */
WhoCommand::WhoCommand() : _query(NONE), _hasOperatorFlag(false) {}

/**
 * Command WHO constructor
 * 
 * @param query The query to search for
 * @param hasOperatorFlag Whether to only show operator users
 */
WhoCommand::WhoCommand(std::string query, bool hasOperatorFlag) : _query(query), _hasOperatorFlag(hasOperatorFlag) {}

/**
 * Destroys the WHO command
 * 
 */
WhoCommand::~WhoCommand() {}

/**
 * Executes the command WHO
 * 
 * @param clientFd The socket file descriptor of the client
 */
void WhoCommand::execute(int clientFd) {
    Server& server = Server::getInstance();
    User& user = server.getUserByFd(clientFd);

    if (this->_query != NONE && (this->_query[0] == '#' || this->_query[0] == '&')) {
        // El canal que coincida con el query, usuarios en el canal
        // Si no coincide ninguno, EndOfWhoResponse solamente (un usuario puede llevar # o & en su nombre??)
        try {
            Channel &channel = server.getChannelByName(this->_query);
            const std::vector<User *> &usersChannel = channel.getAllUsers();

            for (size_t i = 0; i < usersChannel.size(); i++) {
                bool isOper = channel.isOper(usersChannel[i]->getNickname());
                if (this->_hasOperatorFlag && !isOper)
                    continue;
                server.sendMessage(clientFd,
                    WhoReplyResponse(
                        this->_query,
                        usersChannel[i]->getUsername(),
                        usersChannel[i]->getHostname(),
                        usersChannel[i]->getNickname(),
                        isOper ? "@" : NONE,
                        usersChannel[i]->getRealName()
                    ).getReply()
                );
            }
            server.sendMessage(clientFd, EndOfWhoResponse(this->_query).getReply());
        } catch (NoSuchChannelException &e) {
            server.sendMessage(clientFd, EndOfWhoResponse(this->_query).getReply());
        }
    } else if (this->_query != NONE) {
        // El usuario que coincida con el query, rol en los canales en los que esté
        // Si no coincide ninguno, EndOfWhoResponse solamente
        const std::vector<User> &users = server.getUsers();
        for (std::vector<User>::const_iterator it = users.begin(); it != users.end(); it++) {
            if (this->_query != it->getNickname() && this->_query != it->getUsername()
                && this->_query != it->getHostname())
                continue;

        }
        server.sendMessage(clientFd, WhoReplyResponse().getReply());
        server.sendMessage(clientFd, EndOfWhoResponse().getReply());
    } else {
        //lo del else if pero para todos los usuarios
        const std::vector<User> &users = server.getUsers();
        for (std::vector<User>::iterator it = users.begin(); it != users.end(); it++) {
            if (this->_hasOperatorFlag && !it->isOper())
                continue;
            server.sendMessage(clientFd,
                WhoReplyResponse(
                    it->getUsername(),
                    it->getHostname(),
                    it->getServerName(),
                    it->getNickname(),
                    it->isOper() ? "@" : NONE,
                    it->getRealName()
                ).getReply()
            );
        }
    }
}
