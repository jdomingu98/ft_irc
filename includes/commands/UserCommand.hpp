#ifndef USER_COMMAND_HPP
# define USER_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"

# include "CommandException.hpp"

# include "libsUtils.hpp"

/**
 * An ICommand implementation that is responsible for setting the username data of an user.
 */
class UserCommand : public ICommand {
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