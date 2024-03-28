#ifndef INVITE_COMMAND_HPP
# define INVITE_COMMAND_HPP

# include "libsUtils.hpp"
# include "ICommand.hpp"
# include "Server.hpp"

/**
 * A class that represents the command INVITE.
 */
class InviteCommand : public ICommand {
    private:
        std::string _nickname;
        std::string _channelName;

    public:
        InviteCommand();
        InviteCommand(const std::string& nickname, const std::string& channelName);
        ~InviteCommand();

        void execute(int clientFd);
};

#endif