#include "PassCommand.hpp"

/**
 * PassCommand default constructor.
*/
PassCommand::PassCommand(): ICommand(false), _password("") {}

/**
 * PassCommand password constructor.
 * 
 * @param password The password
 */
PassCommand::PassCommand(const std::string& password): ICommand(false), _password(password) {}

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
 * @throws `CommandException` If the password is invalid
 * 
 */
void PassCommand::execute(Server &server, int clientFd) {
    std::cout << "Password: " << this->_password << std::endl;
    if (server.getUserByFd(clientFd).isPasswordChecked())
        throw AlreadyRegisteredException();
    if(server.getUserByFd(clientFd).isRegistered())
        throw CommandException("User has already registered.");
    server.getUserByFd(clientFd).setPassword(_password);
}
