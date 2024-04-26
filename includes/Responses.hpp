#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include <string>

# include "Server.hpp"

// ========================================= IRC COMMAND REPLY MESSAGES =========================================

# define RPL_TOPIC(channel, topic) (channel) + " :" + (topic)
# define RPL_NO_TOPIC(channel) (channel) + " :No topic is set"
# define RPL_INVITING(channel, nickname) (channel) + " " + (nickname)
// # define RPL_CHANNEL_MODE_IS(channel, mode, modeParams) (channel) + " " + (mode) + " " + (modeParams)
# define RPL_END_OF_NAMES(channel) (channel) + " :End of NAMES list."

// # define CHANNEL_MODE_IS_CODE_NUMBER "324"

/**
 * This class represents the responses to the IRC commands.
 */
class Responses {
    private:
        std::string _codeNumber;
        std::string _nickname;
        std::string _replyMsg;
    public:
        Responses(std::string const &codeNumber, std::string const &nickname, std::string const &replyMsg)
            : _codeNumber(codeNumber), _nickname(nickname), _replyMsg(replyMsg) {}
        
        virtual ~Responses() {}
        
        std::string getReply() {
            return RESPONSE_MSG(_codeNumber, _nickname, _replyMsg);
        }
};

/**
 * This class represents the response to the end of the names list.
 */
class EndOfNamesResponse : public Responses {
    public:
        EndOfNamesResponse(std::string const &nickname, std::string const &channel) : Responses("366", nickname, RPL_END_OF_NAMES(channel)) {}
};

/**
 * This class represents the response to an user invitation request.
 */
class InvitingResponse : public Responses {
    public:
        InvitingResponse(std::string const &nickname, std::string const &channel) : Responses("341", nickname, RPL_INVITING(channel, nickname)) {}
};

/**
 * This class represents the response to the names list of the channel where the user joins.
 */
class NamesReplyResponse : public Responses {
    private:
        std::string rplNamesReply(Channel &channel) const;
    public:
        NamesReplyResponse(std::string const &nickname, Channel &channel) : Responses("353", nickname, rplNamesReply(channel)) {}
};

/**
 * This class represents the response to a channel topic request that has been set.
 */
class NoTopicResponse : public Responses {
    public:
        NoTopicResponse(std::string const &nickname, std::string const &channel) : Responses("331", nickname, RPL_NO_TOPIC(channel)) {}
};

/**
 * This class represents the response to a channel topic request that has not been set.
 */
class TopicResponse : public Responses {
    public:
        TopicResponse(std::string const &nickname, std::string const &channel, std::string const &topic) : Responses("332", nickname, RPL_TOPIC(channel, topic)) {}
};

#endif