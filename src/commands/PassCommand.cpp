#include "PassCommand.hpp"

/**
 * PassCommand default constructor.
*/
PassCommand::PassCommand(): _password("") {}

/**
 * PassCommand password constructor.
 * 
 * @param password The password
 */
PassCommand::PassCommand(const std::string& password): _password(password) {}

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
void PassCommand::execute(Server &server, int fd) {
    std::cout << "Password: " << this->_password << std::endl;
    
    if (server.isValidPassword(this->_password))
        server.getUserByFd(fd).checkPassword();
    else 
        throw CommandException("Invalid password");
}
