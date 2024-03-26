#ifndef PRIVATE_MESSAGE_COMMAND_HPP
# define PRIVATE_MESSAGE_COMMAND_HPP

# include "ICommand.hpp"
# include "Server.hpp"
# include "libsUtils.hpp"

/**
 * A class that represents the PRIVMSG command.
 */
class PrivateMessageCommand : public ICommand {
    private:
        std::vector<std::string> _receivers;
        std::string _message;

        PrivateMessageCommand();

    public:
        PrivateMessageCommand(std::vector<std::string> receivers, std::string message);
        void execute(int clientFd);
};

#endif