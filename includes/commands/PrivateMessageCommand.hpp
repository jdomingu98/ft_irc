#ifndef PRIVATE_MESSAGE_COMMAND_HPP
# define PRIVATE_MESSAGE_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for sending a private message to a user or channel.
 */
class PrivateMessageCommand : public ACommand {
    private:
        const std::vector<std::string> _receivers;
        const std::string _message;
    public:
        PrivateMessageCommand(const std::vector<std::string> receivers, const std::string &message);
        void execute(int clientFd);
};

#endif