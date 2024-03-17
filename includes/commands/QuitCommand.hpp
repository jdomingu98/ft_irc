#ifndef QUIT_COMMAND_HPP
# define QUIT_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"
// # include "User.hpp"

# include "ServerException.hpp"

# include "libsUtils.hpp"

/**
 * An ICommand implementation that is responsible for closing the connection with the server.
 */
class QuitCommand : public ICommand {
    private:
        std::string _msg;
    public:
        QuitCommand();
        QuitCommand(std::string msg);
        ~QuitCommand();

        void execute(Server &server, int clientFd);
};

#endif