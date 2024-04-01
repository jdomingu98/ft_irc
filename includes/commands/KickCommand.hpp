#ifndef KICK_COMMAND_HPP
# define KICK_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"

# include "libsUtils.hpp"

class Channel;

class User;

/**
 * An ICommand implementation that is responsible for the kicking of users on channels.
 * 
 */
class KickCommand : public ICommand {
    private:
        std::vector<Channel>    _channels;
        std::vector<User>       _users;
        std::string             _comment;

    public:
        KickCommand(std::vector<Channel> channels, std::vector<User> users, std::string comment);
        ~KickCommand();

        void execute(int clientFd);
};

#endif