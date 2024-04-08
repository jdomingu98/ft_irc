#ifndef PRIVATE_MESSAGE_COMMAND_HPP
# define PRIVATE_MESSAGE_COMMAND_HPP

# include "ACommand.hpp"
# include "Server.hpp"
# include "User.hpp"
# include "libsUtils.hpp"

class User;

/**
 * A class that represents the PRIVMSG command.
 */
class PrivateMessageCommand : public ACommand {
    private:
        std::vector<std::string> _receivers;
        std::string _message;

        PrivateMessageCommand();

    public:
        PrivateMessageCommand(std::vector<std::string> receivers, std::string message);
        void execute(int clientFd);
};

#endif