#include"QuitCommand.hpp"

QuitCommand::QuitCommand() {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(Server &server, int fd) {
    std::string message = "goodbye until another time"
    if(send(fd, message.c_str(), message.length(), 0) < 0) {
        throw CommandException(SEND_EXPT);
    }
    server.removeUser(fd);
    close(fd);
}