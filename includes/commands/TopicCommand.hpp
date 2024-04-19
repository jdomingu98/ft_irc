#ifndef TOPIC_COMMAND_HPP
# define TOPIC_COMMAND_HPP

# include "ACommand.hpp"

# include "Server.hpp"

class Channel;

/**
 * An ACommand implementation that is responsible for setting the topic of a channel.
 */
class TopicCommand : public ACommand {
    private:
        Channel     *_channel;
        std::string _topic;
        bool        _newTopicProvided;
    
    public:
        TopicCommand(Channel *channel);
        TopicCommand(Channel *channel, const std::string& topic);
        ~TopicCommand();

        void execute(int clientFd);
};

#endif