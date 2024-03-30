#ifndef MODE_COMMAND_HPP
# define MODE_COMMAND_HPP

# include "ICommand.hpp"
# include "libsUtils.hpp"
# include "Server.hpp"

typedef enum EMode {
  INVITE_ONLY = 'i',
  TOPIC_PROTECTED = 't',
  CHANNEL_KEY = 'k',
  CHANNEL_OPERATOR = 'o',
  USER_LIMIT = 'l',
} Mode;

class ModeCommand : public ICommand {
    private:
        
        bool _plus;
        std::string _channel;
        std::vector<Mode> _modes;
        std::string _modeParams;

    public:
        void execute(int clientFd);
        ModeCommand(bool plus, const std::string& channel, std::vector<Mode> modes, const std::string& modeParams);
        ~ModeCommand();

        void inviteOnly();
        void topicProtected();
        void channelKey();
        void channelOperator();
        void userLimit();
};

#endif