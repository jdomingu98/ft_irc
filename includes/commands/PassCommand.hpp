#ifndef PASS_COMMAND_HPP
# define PASS_COMMAND_HPP

# include "libsUtils.hpp"
# include "ICommand.hpp"
# include "Server.hpp"
# include "CommandException.hpp"

class PassCommand: public ICommand {
    public:
        PassCommand();
        PassCommand(const std::string& password);
        ~PassCommand();
        void execute(Server &server, int fd);
    private:
        std::string _password;
};

#endif