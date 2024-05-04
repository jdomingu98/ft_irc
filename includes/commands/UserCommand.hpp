#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for setting the username data of an user.
 */
class UserCommand : public ACommand {
    private:
        const std::string _username;
        const std::string _hostname;
        const std::string _serverName;
        const std::string _realName;

    public:
        UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName, const std::string& realName);
        void execute(int clientFd);
};

#endif