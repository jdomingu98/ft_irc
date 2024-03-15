#include "UserCommand.hpp"

/**
 * Command User default constructor
 * 
 */
UserCommand::UserCommand(): _username(""), _hostname(""), _serverName(""), _realName("") {}

/**
 * Command User constructor
 * 
 * @param username The username
 * @param hostname The hostname
 * @param serverName The server name
 * @param realName The real name of the client
 */
UserCommand::UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName,
                            const std::string& realName) : _username(username), _hostname(hostname),
                                                            _serverName(serverName), _realName(realName) {}

/**
 * Command User destructor
 * 
 */
UserCommand::~UserCommand() {}

/**
 * Execute the command USER.
 * 
 * @param server The server where the command will be executed
 * @param fd The socket file descriptor of the client
 * 
 */
void UserCommand::execute(Server &server, int fd) {
    // TODO: If user is already registered, throw exception (AlreadyRegisteredException)
    User user = server.getUserByFd(fd);
    user.setUsername(this->_username);
    user.setHostname(this->_hostname);
    user.setServerName(this->_serverName);
    user.setRealName(this->_realName);
}
