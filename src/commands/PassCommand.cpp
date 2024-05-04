#include "PassCommand.hpp"

/**
 * PassCommand password constructor.
 * 
 * @param password The password
 */
PassCommand::PassCommand(const std::string& password) : ACommand(false), _password(password) {}

/**
 * Execute the command PASS.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `AlreadyRegisteredException` If the user is already registered
 */
void PassCommand::execute(int clientFd) {
    Server& server = Server::getInstance();
	User *user = server.getUserByFd(clientFd);
    if (user->isRegistered())
        throw AlreadyRegisteredException();
    user->setPassword(_password);
}