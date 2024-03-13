#include"QuitCommand.hpp"

QuitCommand::QuitCommand() {}

QuitCommand::QuitCommand(std::string &msg) : _msg(msg) {}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(Server &server, int fd) {
    std::string message = "goodbye until another time"
    if(send(fd, message.c_str(), message.length(), 0) < 0) {
        throw CommandException(SEND_EXPT);
    }
    if(_msg.length() > 0){
        message = "QUIT: " + _msg;
        //send message to all clients on channel and server
    }else{
        message = user.getNickname();
        //send message to all clients on channel and server
    }
    server.removeUser(fd);
    close(fd);
}