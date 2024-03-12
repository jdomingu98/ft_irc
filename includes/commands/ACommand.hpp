#ifndef A_COMMAND_HPP
# define A_COMMAND_HPP

#include "User.hpp"
#include "commands/CommandException.hpp"

class Server;

class ACommand{

    protected:
        static void validatePassword(Server &server, int fd);
    public:
        virtual void execute(Server &server, int fd) = 0;

};

#endif