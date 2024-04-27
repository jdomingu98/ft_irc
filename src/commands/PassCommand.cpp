#include "PassCommand.hpp"

/**
 * PassCommand default constructor.
*/
PassCommand::PassCommand() : ACommand(false), _password(NONE) {}

/**
 * PassCommand password constructor.
 * 
 * @param password The password
 */
PassCommand::PassCommand(const std::string& password) : ACommand(false), _password(password) {}

/**
 * PassCommand destructor.
 */
PassCommand::~PassCommand() {}

/**
 * Execute the command PASS.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `AlreadyRegisteredException` If the user is already registered
 */
void PassCommand::execute(int clientFd) {
    Server& server = Server::getInstance();
    if (server.getUserByFd(clientFd).isRegistered())
        throw AlreadyRegisteredException();
    server.getUserByFd(clientFd).setPassword(this->_password);
}