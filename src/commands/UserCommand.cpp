#include "UserCommand.hpp"

/**
 * Command User default constructor
 * 
 */
UserCommand::UserCommand() : ACommand(false), _username(NONE), _hostname(NONE), _serverName(NONE), _realName(NONE) {}

/**
 * Command User constructor
 * 
 * @param username The username
 * @param hostname The hostname
 * @param serverName The server name
 * @param realName The real name of the client
 */
UserCommand::UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName,
                            const std::string& realName) : ACommand(false), _username(username), _hostname(hostname),
                                                            _serverName(serverName), _realName(realName) {}

/**
 * Command User destructor
 * 
 */
UserCommand::~UserCommand() {}

/**
 * Execute the command USER.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `AlreadyRegisteredException` If the user has already used the USER command
 */
void UserCommand::execute(int clientFd) {
    Server& server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);
    if (!user.getUsername().empty())
        throw AlreadyRegisteredException();
    user.setUsername(this->_username);
    user.setHostname(this->_hostname);
    user.setServerName(this->_serverName);
    user.setRealName(this->_realName);
    if (user.canRegister())
        server.attemptUserRegistration(clientFd);
}