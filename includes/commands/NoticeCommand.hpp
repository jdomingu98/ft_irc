#ifndef NOTICE_COMMAND_HPP
# define NOTICE_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for sending a notice to a user or channel.
 */
class NoticeCommand : public ACommand {
    private:
        std::vector<std::string> _receivers;
        std::string _message;

        NoticeCommand();

    public:
        NoticeCommand(std::vector<std::string> receivers, std::string message);
        void execute(int clientFd);
};

#endif