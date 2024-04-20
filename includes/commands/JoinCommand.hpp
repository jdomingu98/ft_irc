#ifndef JOIN_COMMAND_HPP
# define JOIN_COMMAND_HPP

# include <map>

# include "ACommand.hpp"

# include "Server.hpp"

class Channel;

class User;

/**
 * An ACommand implementation that is responsible for the binding and creation of a channel.
 * 
 */
class JoinCommand : public ACommand {
    private:
        std::map<std::string, std::string> _channels; //key: channelName, value: channelPassword

        std::string rplNamReply(const std::string &nickname,
                                    const std::string &username,
                                    const std::string &hostname,
                                    const Channel &channel) const;
        void printUsers(Channel &channel) const;
        void sendMessages(int clientFd, Channel &channel) const;

    public:
        JoinCommand(std::map<std::string, std::string> channelMap);
        ~JoinCommand();

        void execute(int clientFd);
};

#endif