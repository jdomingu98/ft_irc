#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include "Channel.hpp"

class Channel;

// ========================================= IRC COMMAND REPLY MESSAGES =========================================

# define SERVER_NAME "irc.ft_messenger.net"
# define SERVER_VERSION "ft_messenger-v1.0.0"
# define AVAILABLE_CHANNEL_MODES "iklot"

# define RESPONSE_MSG(codeNumber, nickname, replyMsg) ":" + std::string(SERVER_NAME) + " " + (codeNumber) + " " + (nickname) + " " + (replyMsg)

# define RPL_TOPIC(channel, topic) (channel) + " :" + (topic)
# define RPL_NO_TOPIC(channel) (channel) + " :No topic is set"
# define RPL_INVITING(channel, nickname) (channel) + " " + (nickname)
# define RPL_END_OF_NAMES(channel) (channel) + " :End of NAMES list"
# define RPL_CHANNEL_MODE_IS(channel, mode, modeParams) (channel) + " " + (mode) + " " + (modeParams)
# define RPL_WHO_REPLY(channel, user, host, nick, userType, realname) (channel) + " " + (user) + " " + (host) + " " + SERVER_NAME + " " + (nick) + "H" + (userType) + " :0 " + (realname)
# define END_OF_WHO(name) (name) + " :End of WHO list"
# define RPL_DOWNLOAD(filename) ":File " + (filename) + " has been downloaded successfully"

# define USER_ID(nickname, username, hostname) ":" + (nickname) + "!" + (username) + "@" + (hostname)

# define RPL_WELCOME "Welcome to the Internet Relay Network "
# define RPL_YOUR_HOST(servername) "Your host is " + (servername) + ", running version " + SERVER_VERSION
# define RPL_CREATED(date) "This server was created " + (date)
# define RPL_MY_INFO(servername) (servername) + " " + SERVER_VERSION + " Available user modes: , Available channel modes: " + AVAILABLE_CHANNEL_MODES

# define CMD_MSG(nickname, username, hostname, message) USER_ID(nickname, username, hostname) + " " + (message)

# define INVITE_MSG(invitedUser, channel) "INVITE " + (invitedUser) + " " + (channel)
# define JOIN_MSG(channelName) "JOIN " + (channelName)
# define KICK_MSG(channelName, kickedUser, comment) "KICK " + (channelName) + " " + (kickedUser) + " :" + (comment)
# define MODE_MSG(channel, flag, modeParams) "MODE " + (channel) + " " + (flag) + " " + (modeParams)
# define NICK_MSG(nickname) "NICK " + (nickname)
# define PART_MSG(channelName) "PART " + (channelName)
# define PRIVMSG_MSG(destination, message) "PRIVMSG " + (destination) + " :" + (message)
# define NOTICE_MSG(destination, message) "NOTICE " + (destination) + " :" + (message)
# define QUIT_MSG(message) "QUIT :" + (message)
# define TOPIC_MSG(channelName, topic) "TOPIC " + (channelName) + " " + (topic)
# define UP_MSG(nickname, filename, channel) "UP " + (nickname) + " " + (filename) + " " + (channel)

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

/**
 * This class represents the response to a channel mode consult.
 */
class ChannelModeIsResponse : public Responses {
    public:
        ChannelModeIsResponse(std::string const &nickname, std::string const &channel, std::string const &mode, std::string const &modeParams) : Responses("324", nickname, RPL_CHANNEL_MODE_IS(channel, mode, modeParams)) {}
};

/**
 * This class represents the response to the Who command request
*/
class WhoReplyResponse : public Responses {
    public:
        WhoReplyResponse(
            std::string const &channel,
            std::string const &nickname,
            std::string const &username,
            std::string const &hostname,
            std::string const &userType,
            std::string const &realname
        ): Responses("352", nickname, RPL_WHO_REPLY(channel, username, hostname, nickname, userType, realname)) {}
};

/**
 * This class represents the response to the end of the Who command request.
*/
class EndOfWhoResponse : public Responses {
    public:
        EndOfWhoResponse(std::string const &nickname) : Responses("315", nickname, END_OF_WHO(nickname)) {}
};

/**
 * This class represents the response to the welcome message.
 */
class WelcomeResponse : public Responses {
    public:
        WelcomeResponse(std::string const &nickname, std::string const &username, std::string const &hostname) : Responses("001", nickname, std::string(RPL_WELCOME) + USER_ID(nickname, username, hostname)) {}
};

/**
 * This class represents the response to the welcome message.
 * This response refers to the users host.
 */
class YourHostResponse : public Responses {
    public:
        YourHostResponse(std::string const &nickname, std::string const &servername) : Responses("002", nickname, RPL_YOUR_HOST(servername)) {}
};

/**
 * This class represents the response to the welcome message.
 * This response refers to the server creation date.
 */
class CreatedResponse : public Responses {
    public:
        CreatedResponse(std::string const &nickname, std::string const &date) : Responses("003", nickname, RPL_CREATED(date)) {}
};

/**
 * This class represents the response to the welcome message.
 * This response refers to the user information.
 */
class MyInfoResponse : public Responses {
    public:
        MyInfoResponse(std::string const &nickname, std::string const &servername) : Responses("004", nickname, RPL_MY_INFO(servername)) {}
};

class DownloadResponse : public Responses {
    public:
        DownloadResponse(std::string const &nickname, std::string const &filename) : Responses("042", nickname, RPL_DOWNLOAD(filename)) {}
};

#endif