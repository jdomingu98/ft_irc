#ifndef QUITCOMMAND_HPP
# define QUITCOMMAND_HPP

# include "libsUtils.hpp"
# include "ICommand.hpp"
# include "Server.hpp"
# include "CommandException.hpp"

class QuitCommand: public ICommand
{
    public:
        QuitCommand();
        ~QuitCommand();
        void execute(Server &server, int fd);
};

#endif