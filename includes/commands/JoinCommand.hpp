#ifndef JOIN_COMMAND_HPP
# define JOIN_COMMAND_HPP

# include <map>

# include "ICommand.hpp"

# include "Server.hpp"

# include "libsUtils.hpp"

class Channel;

class User;

/**
 * An ICommand implementation that is responsible for the binding and creation of a channel.
 * 
 */
class JoinCommand : public ICommand {
    private:
        std::map<std::string, std::string> _channels; //key: channelName, value: channelPassword

        std::string rplNamReply(std::string const &channelName,
                                std::vector<User> const &opers,
                                std::vector<User> const &users) const;
        void printUsers(Channel &channel) const;
        void sendMessages(int clientFd, const std::string &message, Channel &channel) const;

    public:
        JoinCommand(std::map<std::string, std::string> channelMap);
        ~JoinCommand();

        void execute(int clientFd);
};

#endif