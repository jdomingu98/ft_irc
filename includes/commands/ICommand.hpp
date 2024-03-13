#ifndef I_COMMAND_HPP
# define I_COMMAND_HPP

class Server;

/**
 * An interface that represents a command that can be executed by the server.
 */
class ICommand {
    public:
        virtual void execute(Server &server, int fd) = 0;
};

#endif