#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include "IRCException.hpp"
# include "ServerException.hpp"
# include "CommandNotFoundException.hpp"

// ========================================= IRC COMMAND ERROR MESSAGES =========================================

//RPL_XXX -> Reply messages (Command Response)

# define ERR_NEED_MORE_PARAMS " :Not enough parameters"
# define ERR_ALREADY_REGISTERED ":You may not reregister"

# define ERR_NO_NICKNAME_GIVEN ":No nickname given"
# define ERR_ERRONEOUS_NICKNAME " :Erroneous nickname"
# define ERR_NICKNAME_IN_USE " :Nickname is already in use"
# define ERR_NICK_COLLISION " :Nickname collision KILL"

// # define ERR_BANNED_FROM_CHAN(channel) (channel) " :Cannot join channel (+b)"
// # define ERR_INVITE_ONLY_CHAN(channel) (channel) " :Cannot join channel (+i)"
// # define ERR_BAD_CHANNEL_KEY(channel) (channel) " :Cannot join channel (+k)"
// # define ERR_CHANNEL_IS_FULL(channel) (channel) " :Cannot join channel (+l)"
// // # define ERR_BAD_CHAN_MASK ""
// # define ERR_NO_SUCH_CHANNEL(channelName) (channelName) " :No such channel"
// # define ERR_TOO_MANY_CHANNELS(channelName) (channelName) " :You have joined too many channels"
// # define RPL_TOPIC(channel, topic) (channel) " :" (topic)

// #define ERR_NOT_ON_CHANNEL(channel) (channel) " :You're not on that channel"

// #define RPL_NO_TOPIC(channel) (channel) " :No topic is set"
// #define ERR_CHAN_O_PRIVS_NEEDED(channel) (channel) " :You're not channel operator"

// #define ERR_NO_SUCH_NICK(nickname) (nickname) " :No such nick/channel"
// #define ERR_USER_ON_CHANNEL(nickname, channel) (nickname) " " (channel) " :is already on channel"
// #define RPL_INVITING(channel, nickname) (channel) " " (nickname)
// #define RPL_AWAY(nickname, awayMessage) (nickname) " :" (awayMessage)

#define ERR_NO_RECIPIENT(command) (":No recipient given (" + command + ")")
#define ERR_NO_TEXT_TO_SEND ":No text to send"
// #define ERR_CANNOT_SEND_TO_CHAN(channel) (channel) " :Cannot send to channel"
// #define ERR_NO_TOP_LEVEL(mask) (mask) " :No toplevel domain specified"
// #define ERR_WILD_TOP_LEVEL(mask) (mask) " :Wildcard in toplevel domain"
// #define ERR_TOO_MANY_TARGETS(target)  (target)" :Duplicate recipients. No message delivered"

// #define RPL_CHANNEL_MODE_IS(channel, mode, modeParams) (channel) " " (mode) " " (modeParams)
// #define ERR_KEYSET(channel) (channel) " :Channel key already set"
// #define RPL_BAN_LIST (channe, banId) (channel) " " (banId)
// #define RPL_END_OF_BAN_LIST(channel)  (channel) " :End of channel ban list"
// #define ERR_UNKOWN_MODE (modeChar) (modeChar) " :is unknown mode char to me"
// #define ERR_USERS_DONT_MATCH ":Cant change mode for other users"
// #define ERR_U_MODE_IS(userModeString) (userModeString)
// #define ERR_U_MODE_UNKNOWN_FLAG ":Unknown MODE flag"

// ==================================================================================


/**
 * This exception is thrown when an user attempts to register with the server when it is already registered.
 */
class AlreadyRegisteredException : public IRCException {
    public:
        AlreadyRegisteredException() : IRCException("462", ERR_ALREADY_REGISTERED) {}
};

/**
 * This exception is thrown when a nickname is erroneous. (Invalid characters, so long, etc.)
 */
class ErroneousNicknameException : public IRCException {
    public:
        ErroneousNicknameException(const std::string nickname) : IRCException("432", nickname + ERR_ERRONEOUS_NICKNAME) {}
};

/**
 * This exception is thrown when a command is missing parameters.
 */
class NeedMoreParamsException : public IRCException {
    public:
        NeedMoreParamsException(const std::string command) : IRCException("461", command + ERR_NEED_MORE_PARAMS) {}
};

/**
 * This exception is thrown when a nickname is already in use. (Nickname collision)
 * It is thrown when a user tries to set a nickname the first time, and it is already in use.
 */
class NickCollisionException : public IRCException {
    public:
        NickCollisionException(const std::string nickname) : IRCException("436", nickname + ERR_NICK_COLLISION) {}
};

/**
 * This exception is thrown when a nickname is already in use.
 * It is thrown when a client tries to change their nickname to one that is already in use.
 */
class NicknameInUseException : public IRCException {
    public:
        NicknameInUseException(const std::string nickname) : IRCException("433", nickname + ERR_NICKNAME_IN_USE) {}
};

/**
 * This exception is thrown when a nickname is not given in a command that requires one.
 */
class NoNicknameGivenException : public IRCException {
    public:
        NoNicknameGivenException() : IRCException("431", ERR_NO_NICKNAME_GIVEN) {}
};

/**
 * This exception is thrown when a command is given before the user is registered.
 */
class NotRegisteredException : public IRCException {
    public:
        NotRegisteredException() : IRCException("451", ":You have not registered") {}
};

/**
 * This exception is thrown when a password is incorrect.
 */
class PasswordMismatchException : public IRCException {
    public:
        PasswordMismatchException() : IRCException("464", ":Password incorrect") {}
};

class NoRecipientGivenException : public IRCException {
    public:
        NoRecipientGivenException(const std::string command) : IRCException("411", ERR_NO_RECIPIENT(command)) {}
};

class NoTextToSendException : public IRCException {
    public:
        NoTextToSendException() : IRCException("412", ERR_NO_TEXT_TO_SEND) {}
};

#endif