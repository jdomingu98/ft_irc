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
        const bool _plus;
        const bool _showChannelModes;
        Channel &_channel;
        const std::vector<Mode> _modes;
        const std::vector<std::string> _modeParams;

        bool modeNeedsParam(Mode mode) const;

    public:
        void execute(int clientFd);
        ModeCommand(const bool plus, const std::string &channel, const std::vector<Mode> &modes, const std::vector<std::string> &modeParams);
        ModeCommand(const std::string &channel);

        void inviteOnly();
        void topicProtected();
        void channelKey(const std::string &param);
        void channelOperator(const std::string &param);
        void userLimit(const std::string &param);
};

#endif