#ifndef QUIT_COMMAND_HPP
# define QUIT_COMMAND_HPP

# include "ACommand.hpp"

# include "Server.hpp"
// # include "User.hpp"

# include "libsUtils.hpp"

/**
 * An ACommand implementation that is responsible for closing the connection with the server.
 */
class QuitCommand : public ACommand {
    private:
        std::string _msg;
    public:
        QuitCommand();
        QuitCommand(std::string msg);
        ~QuitCommand();

        void execute(int clientFd);
};

#endif