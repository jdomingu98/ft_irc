#ifndef QUIT_COMMAND_HPP
# define QUIT_COMMAND_HPP

# include "ACommand.hpp"

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for closing the connection with the server.
 */
class QuitCommand : public ACommand {
    private:
        std::string _message;
    public:
        QuitCommand(std::string message);
        ~QuitCommand();

        void execute(int clientFd);
};

#endif