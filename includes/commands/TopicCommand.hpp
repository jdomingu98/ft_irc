#ifndef TOPIC_COMMAND_HPP
# define TOPIC_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"

# include "libsUtils.hpp"


/**
 * An ICommand implementation that is responsible for setting the topic of a channel.
 * 
 */
class TopicCommand : public ICommand {
    private:
        Channel     _channel;
        std::string _topic;
    
    public:
        TopicCommand(const Channel& channel);
        TopicCommand(const Channel& channel, const std::string& topic);
        ~TopicCommand();

        void execute(int clientFd);
};

#endif