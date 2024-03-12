#ifndef PASS_COMMAND_HPP
# define PASS_COMMAND_HPP

# include "libsUtils.hpp"
# include "ACommand.hpp"
# include "Server.hpp"

class Server;

class PassCommand: public ACommand {
    public:
        PassCommand();
        PassCommand(const std::string& password);
        ~PassCommand();
        void execute(Server &server, int fd);
    private:
        std::string _password;
};

#endif