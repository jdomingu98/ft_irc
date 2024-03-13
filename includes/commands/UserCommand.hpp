#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "libsUtils.hpp"
# include "ICommand.hpp"
# include "Server.hpp"
# include "CommandException.hpp"

class UserCommand: public ICommand {
    private:
        std::string _username;
        std::string _hostname;
        std::string _serverName;
        std::string _realName;

    public:
        UserCommand();
        UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName, const std::string& realName);
        void execute(Server &server, int fd);
        ~UserCommand();
};

#endif