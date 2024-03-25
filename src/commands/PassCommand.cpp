#include "PassCommand.hpp"

/**
 * PassCommand default constructor.
*/
PassCommand::PassCommand() : ICommand(false), _password("") {}

/**
 * PassCommand password constructor.
 * 
 * @param password The password
 */
PassCommand::PassCommand(const std::string& password) : ICommand(false), _password(password) {}

/**
 * PassCommand destructor.
 */
PassCommand::~PassCommand() {}

/**
 * Execute the command PASS.
 * 
 * @param server The server where the command will be executed
 * @param fd The socket file descriptor of the client
 * 
 * @throws `AlreadyRegisteredException` If the user is already registered
 * 
 */
void PassCommand::execute(Server &server, int clientFd) {
    if (server.getUserByFd(clientFd).isRegistered())
        throw AlreadyRegisteredException();
    server.getUserByFd(clientFd).setPassword(this->_password);
}
