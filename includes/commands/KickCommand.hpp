#ifndef KICK_COMMAND_HPP
# define KICK_COMMAND_HPP

# include "ACommand.hpp"

# include "Server.hpp"

class Channel;

class User;

/**
 * An ACommand implementation that is responsible for the kicking of users on channels.
 * 
 */
class KickCommand : public ACommand {
    private:
        const std::vector<std::string>  _channels;
        const std::vector<User>         _users;
        const std::string               _comment;

        void kickUserFromChannel(const Channel &channel, const std::string &nickname, const std::string &kickedUser, const std::string &comment);

    public:
        KickCommand(const std::vector<std::string> &channels, const std::vector<User> &users, const std::string &comment);
        ~KickCommand();

        void execute(int clientFd);
};

#endif