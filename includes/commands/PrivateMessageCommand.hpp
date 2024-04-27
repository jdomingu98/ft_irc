#ifndef PRIVATE_MESSAGE_COMMAND_HPP
# define PRIVATE_MESSAGE_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for sending a private message to a user or channel.
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