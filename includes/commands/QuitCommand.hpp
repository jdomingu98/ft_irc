#ifndef QUITCOMMAND_HPP
# define QUITCOMMAND_HPP

# include "libsUtils.hpp"
# include "ICommand.hpp"
# include "Server.hpp"
# include "CommandException.hpp"

class QuitCommand: public ICommand
{
    private:
        std::string _msg;
    public:
        QuitCommand();
        QuitCommand(std::string &msg);
        ~QuitCommand();
        void execute(Server &server, int fd);
};

#endif