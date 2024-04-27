#ifndef MODE_COMMAND_HPP
# define MODE_COMMAND_HPP

# include "Server.hpp"

/**
 * The different modes that a channel can have.
 */
typedef enum EMode {
    INVITE_ONLY = 'i',
    TOPIC_PROTECTED = 't',
    CHANNEL_KEY = 'k',
    CHANNEL_OPERATOR = 'o',
    USER_LIMIT = 'l',
} Mode;

/**
 * An ACommand implementation that is responsible for setting the modes of a channel.
 * 
 */
class ModeCommand : public ACommand {
    private:

        bool _plus;
        Channel &_channel;
        std::vector<Mode> &_modes;
        std::vector<std::string> &_modeParams;

        bool modeNeedsParam(Mode mode);

    public:
        void execute(int clientFd);
        ModeCommand(bool plus, const std::string& channel, std::vector<Mode> modes, std::vector<std::string>& modeParams);
        ~ModeCommand();

        void inviteOnly();
        void topicProtected();
        void channelKey(const std::string & param);
        void channelOperator(const User &me, const std::string & param);
        void userLimit(const std::string & param);
};

#endif