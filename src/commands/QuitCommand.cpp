#include "QuitCommand.hpp"

/**
 * QuitCommand default constructor.
 */
QuitCommand::QuitCommand() : ICommand(false), _msg("") {}

/**
 * QuitCommand message constructor.
 * 
 * @param msg The message
 */
QuitCommand::QuitCommand(std::string msg) : ICommand(false), _msg(msg) {}

/**
 * QuitCommand destructor.
 */
QuitCommand::~QuitCommand() {}

/**
 * Execute the command QUIT.
 * 
 * @param server The server where the command will be executed
 * @param clientFd The socket file descriptor of the client
 * 
 */
void QuitCommand::execute(Server &server, int clientFd) {
    if (_msg.length() == 0) {
        // message = user.getNickname();
        //send message to all clients on channel and server
    }
    server.removeUser(clientFd);
}