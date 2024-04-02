#ifndef TOPIC_COMMAND_HPP
# define TOPIC_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"

# include "libsUtils.hpp"

class Channel;

/**
 * An ICommand implementation that is responsible for setting the topic of a channel.
 * 
 */
class TopicCommand : public ICommand {
    private:
        Channel     *_channel;
        std::string _topic;
    
    public:
        TopicCommand(Channel *channel);
        TopicCommand(Channel *channel, const std::string& topic);
        ~TopicCommand();

        void execute(int clientFd);
};

#endif