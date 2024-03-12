#include"ACommand.hpp"

void ACommand::validatePassword(Server &server, int fd) {
    User user = server.getUser(fd);
    if (user.isPasswordChecked() == false) {
        throw CommandException("Need password first to continue.");
    }
}