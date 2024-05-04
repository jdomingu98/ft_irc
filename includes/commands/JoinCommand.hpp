#ifndef JOIN_COMMAND_HPP
# define JOIN_COMMAND_HPP

# include "Channel.hpp"

class Channel;

/**
 * An ACommand implementation that is responsible for the binding and creation of a channel.
 * 
 */
class JoinCommand : public ACommand {
    private:
        const std::map<std::string, std::string> _channels; //<name, password>

        void sendMessages(int clientFd, const Channel &channel) const;
    public:
        JoinCommand(const std::map<std::string, std::string> channels);

        void execute(int clientFd);
};

#endif