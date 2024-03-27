#ifndef TOPICCOMMAND_HPP
# define TOPICCOMMAND_HPP

# include "Channel.hpp"
# include "ICommand.hpp"
# include "libsUtils.hpp"
# include "Server.hpp"
# include "User.hpp"

class TopicCommand : public ICommand {
    private:
        std::string _channelName;
        std::string _topic;
    
    public:
        TopicCommand(const std::string& channelName);
        TopicCommand(const std::string& channelName, const std::string& topic);
        ~TopicCommand();

        void execute(int clientFd);
};

#endif