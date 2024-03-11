#ifndef I_COMMAND_HPP
# define I_COMMAND_HPP

class Server;

class ICommand {
    public:
        virtual void execute(Server &server, int fd) = 0;
};

#endif