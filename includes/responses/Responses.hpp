#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include <string>

# include "IRCResponse.hpp"

// ========================================= IRC COMMAND RESPONSE MESSAGES =========================================

# define RPL_TOPIC(channel, topic) (channel) + " :" + (topic)
# define RPL_NO_TOPIC(channel) (channel) + " :No topic is set"
# define RPL_INVITING(channel, nickname) (channel) + " " + (nickname)
//# define RPL_AWAY(nickname, awayMessage) (nickname) + " :" + (awayMessage)
//# define RPL_CHANNEL_MODE_IS(channel, mode, modeParams) (channel) + " " + (mode) + " " + (modeParams)
# define RPL_END_OF_NAMES(channel) (channel) + " :End of NAMES list."

// ==================================================================================

/**
 * This response is sent to a client when an user wants to consult the topic of a channel and it is set.
 */
class RPLTopicResponse : public IRCResponse {
    public:
        RPLTopicResponse(const std::string &channel, const std::string &nickname, const std::string &topic)
            : IRCResponse("332", nickname, RPL_TOPIC(channel, topic)) {}
};

/**
 * This response is sent to a client when an user wants to consult the topic of a channel and it is not set.
 */
class RPLNoTopicResponse : public IRCResponse {
    public:
        RPLNoTopicResponse(const std::string &channel, const std::string &nickname)
            : IRCResponse("331", nickname, RPL_NO_TOPIC(channel)) {}
};

/**
 * This response is sent to a client when an user is invited to a channel.
 */
class RPLInvitingResponse : public IRCResponse {
    public:
        RPLInvitingResponse(const std::string &channel, const std::string &nickname)
            : IRCResponse("341", nickname, RPL_INVITING(channel, nickname)) {}
};

/**
 * This response is sent to a client when an user is away.
 */
/*class RPLAwayResponse : public IRCResponse {
    public:
        RPLAwayResponse(const std::string &nickname, const std::string &awayMessage)
            : IRCResponse("301", nickname, RPL_AWAY(nickname, awayMessage)) {}
};*/

/**
 * This response is sent to a client when an user wants to consult the mode of a channel.
 */
/*class RPLChannelModeIsResponse : public IRCResponse {
    public:
        RPLChannelModeIsResponse(const std::string &nickname, const std::string &channel, const std::string &mode, const std::string &modeParams)
            : IRCResponse("324", nickname, RPL_CHANNEL_MODE_IS(channel, mode, modeParams)) {}
};*/

/**
 * This response is sent to a client when the user joins a channel.
 * It shows the list of users in the channel.
 */
class RPLNamesReplyResponse : public IRCResponse {
    private:
        std::string replyMessage(const std::string &nickname, const Channel &channel);
    public:
        RPLNamesReplyResponse(const std::string &nickname, Channel &channel)
            : IRCResponse("353", nickname, replyMessage(nickname, channel)) {}
};

/**
 * This response is sent to a client when the list of users in a channel is over.
 */
class RPLEndOfNamesResponse : public IRCResponse {
    public:
        RPLEndOfNamesResponse(const std::string &nickname, const std::string &channel)
            : IRCResponse("366", nickname, RPL_END_OF_NAMES(channel)) {}
};

#endif