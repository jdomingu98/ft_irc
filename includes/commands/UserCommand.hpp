#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "ACommand.hpp"

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for setting the username data of an user.
 */
class UserCommand : public ACommand {
    private:
        std::string _username;
        std::string _hostname;
        std::string _serverName;
        std::string _realName;

    public:
        UserCommand();
        UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName, const std::string& realName);
        void execute(int clientFd);
        ~UserCommand();
};

#endif