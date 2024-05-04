#ifndef INVITE_COMMAND_HPP
# define INVITE_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for inviting a user to a channel.
 * 
 */
class InviteCommand : public ACommand {
    private:
        const std::string _nickname;
        const std::string _channelName;

    public:
        InviteCommand(const std::string& nickname, const std::string& channelName);

        void execute(int clientFd);
};

#endif