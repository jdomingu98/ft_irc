#include "UserCommand.hpp"

/**
 * Command User constructor
 * 
 * @param username The username
 * @param hostname The hostname
 * @param serverName The server name
 * @param realName The real name of the client
 */
UserCommand::UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName,
                            const std::string& realName)
    : ACommand(false), _username(username), _hostname(hostname),
                        _serverName(serverName), _realName(realName) {}

/**
 * Execute the command USER.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `AlreadyRegisteredException` If the user has already used the USER command
 */
void UserCommand::execute(int clientFd) {
    Server& server = Server::getInstance();
    User *user = server.getUserByFd(clientFd);

    if (user->isRegistered() && !user->getUsername().empty())
        throw AlreadyRegisteredException();
    user->setUsername(_username);
    user->setHostname(_hostname);
    user->setServerName(_serverName);
    user->setRealName(_realName);
    if (user->canRegister())
        user->makeRegistration();
}