#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include "IRCException.hpp"
# include "ServerException.hpp"

// ========================================= IRC COMMAND ERROR MESSAGES =========================================

# define ERR_NEED_MORE_PARAMS(command)  (command) + " :Not enough parameters"
# define ERR_NOT_REGISTERED ":You have not registered"
# define ERR_ALREADY_REGISTERED ":You may not reregister"
# define ERR_UNKNOWN_COMMAND(command) (command) + " :Unknown command"

# define ERR_NO_NICKNAME_GIVEN ":No nickname given"
# define ERR_ERRONEUS_NICKNAME(nick)  (nick) + " :Erroneus nickname"
# define ERR_NICKNAME_IN_USE(nick) (nick) + " :Nickname is already in use"
# define ERR_NICK_COLLISION(nick) (nick) + " :Nickname collision KILL"
# define ERR_PASSWD_MISMATCH ":Password incorrect"

# define ERR_INVITE_ONLY_CHAN(channel) (channel) + " :Cannot join channel (+i)"
# define ERR_BAD_CHANNEL_KEY(channel) (channel) + " :Cannot join channel (+k)"
# define ERR_CHANNEL_IS_FULL(channel) (channel) + " :Cannot join channel (+l)"
# define ERR_BAD_CHAN_MASK(channel) (channel) + " :Bad Channel Mask"
# define ERR_NO_SUCH_CHANNEL(channelName) (channelName) + " :No such channel"
# define ERR_TOO_MANY_CHANNELS(channelName) (channelName) + " :You have joined too many channels"

# define ERR_NOT_ON_CHANNEL(channel)  (channel) + " :You're not on that channel"

# define ERR_CHANOP_PRIVS_NEEDED(channel)  (channel) + " :You're not channel operator"

# define ERR_NO_SUCH_NICK(nickname) (nickname) + " :No such nick/channel"
# define ERR_USER_ON_CHANNEL(user, channel) (user) + " " + (channel) + " :is already on channel"
# define ERR_USER_NOT_IN_CHANNEL(user, channel) (user) + " " + (channel) + " :They aren't on that channel"

# define ERR_NO_RECIPIENT(command) ":No recipient given (" + (command) + ")"
# define ERR_NO_TEXT_TO_SEND ":No text to send"
# define ERR_CANNOT_SEND_TO_CHAN(channel) (channel) + " :Cannot send to channel"
#define ERR_MISSING_COLON(command) (command) + " :Missing colon"
// # define ERR_NO_TOP_LEVEL(mask) (mask) + " :No toplevel domain specified"
// # define ERR_WILD_TOP_LEVEL(mask) (mask) + " :Wildcard in toplevel domain"
// # define ERR_TOO_MANY_TARGETS(target)  (target)" + :Duplicate recipients. No message delivered"

// #define ERR_KEYSET(channel) (channel) " :Channel key already set"
# define ERR_UNKOWN_MODE(modeChar) (modeChar + " :is unknown mode char to me")
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
        ErroneousNicknameException(const std::string &nickname) : IRCException("432", ERR_ERRONEUS_NICKNAME(nickname)) {}
};

/**
 * This exception is thrown when a command is missing parameters.
 */
class NeedMoreParamsException : public IRCException {
    public:
        NeedMoreParamsException(const std::string &command) : IRCException("461", ERR_NEED_MORE_PARAMS(command)) {}
};

/**
 * This exception is thrown when a nickname is already in use. (Nickname collision)
 * It is thrown when a user tries to set a nickname the first time, and it is already in use.
 */
class NickCollisionException : public IRCException {
    public:
        NickCollisionException(const std::string &nickname) : IRCException("436", ERR_NICK_COLLISION(nickname)) {}
};

/**
 * This exception is thrown when a nickname is already in use.
 * It is thrown when a client tries to change their nickname to one that is already in use.
 */
class NicknameInUseException : public IRCException {
    public:
        NicknameInUseException(const std::string &nickname) : IRCException("433", ERR_NICKNAME_IN_USE(nickname)) {}
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
        NotRegisteredException() : IRCException("451", ERR_NOT_REGISTERED) {}
};

/**
 * This exception is thrown when a password is incorrect.
 */
class PasswordMismatchException : public IRCException {
    public:
        PasswordMismatchException() : IRCException("464", ERR_PASSWD_MISMATCH) {}
};

/**
 * This exception is thrown when an user attemps to join a channel that is invite-only and it was not invited.
 */
class InviteOnlyChanException : public IRCException {
    public:
        InviteOnlyChanException(const std::string &channelName) : IRCException("473", ERR_INVITE_ONLY_CHAN(channelName)) {}
};

/**
 * This exception is thrown when a channel password is incorrect.
 */
class BadChannelKeyException : public IRCException {
    public:
        BadChannelKeyException(const std::string &channelName) : IRCException("475", ERR_BAD_CHANNEL_KEY(channelName)) {}
};

/**
 * This exception is thrown when the channel is full
 */
class ChannelIsFullException : public IRCException {
    public:
        ChannelIsFullException(const std::string &channelName) : IRCException("471", ERR_CHANNEL_IS_FULL(channelName)) {}
};

/**
 * This exception is thrown when a user joins too many channels.
 */
class TooManyChannelsException : public IRCException {
    public:
        TooManyChannelsException(const std::string &channelName) : IRCException("405", ERR_TOO_MANY_CHANNELS(channelName)) {}
};

/**
 * This exception is thrown when the command does not provide a client or channel to send a message.
 */
class NoRecipientGivenException : public IRCException {
    public:
        NoRecipientGivenException(const std::string &command) : IRCException("411", ERR_NO_RECIPIENT(command)) {}
};

/**
 * This exception is thrown when the command does not provide a text to send.
 */
class NoTextToSendException : public IRCException {
    public:
        NoTextToSendException() : IRCException("412", ERR_NO_TEXT_TO_SEND) {}
};

/**
 * This exception is thrown when the user or channel is not found.
 */
class NoSuchNickException : public IRCException {
    public:
        NoSuchNickException(const std::string &nickname) : IRCException("401", ERR_NO_SUCH_NICK(nickname)) {}
};

/**
 * This exception is thrown when the user is not on the channel.
 */
class NotOnChannelException : public IRCException {
    public:
        NotOnChannelException(const std::string &channelName) : IRCException("442", ERR_NOT_ON_CHANNEL(channelName)) {}
};

/**
 * This exception is thrown when the user invited is already on the channel.
 */
class UserOnChannelException : public IRCException {
    public:
        UserOnChannelException(const std::string &nickname, const std::string &channelName)
            : IRCException("443", ERR_USER_ON_CHANNEL(nickname, channelName)) {}
};

/**
 * This exception is thrown when the user needs to be an operator to perform the action.
 */
class ChanOPrivsNeededException : public IRCException {
    public:
        ChanOPrivsNeededException(const std::string &channelName) : IRCException("482", ERR_CHANOP_PRIVS_NEEDED(channelName)) {}
};

/**
 * This exception is thrown when the channel searched does not exist.
 */
class NoSuchChannelException : public IRCException {
    public:
        NoSuchChannelException(const std::string &channelName) : IRCException("403", ERR_NO_SUCH_CHANNEL(channelName)) {}
};

/**
 * This exception is thrown when the channel name is invalid.
 */
class BadChannelMaskException : public IRCException {
    public:
        BadChannelMaskException(const std::string &channelName) : IRCException("476", ERR_BAD_CHAN_MASK(channelName)) {}
};

/**
 * This exception is thrown when the user is not in the channel.
 */
class UserNotInChannelException : public IRCException {
    public:
        UserNotInChannelException(const std::string &nickname, const std::string &channelName)
            : IRCException("441", ERR_USER_NOT_IN_CHANNEL(nickname, channelName)) {}
};

/**
 * This exception is thrown when the specified channel mode does not exist.
 */
class UnknownModeException : public IRCException {
    public:
        UnknownModeException(char modeChar) : IRCException("472", ERR_UNKOWN_MODE(modeChar)) {}
};

/**
 * This exception is thrown when the user tries to send a message to a channel that does not exist.
 */
class CannotSendToChanException : public IRCException {
    public:
        CannotSendToChanException(const std::string &channelName) : IRCException("404", ERR_CANNOT_SEND_TO_CHAN(channelName)) {}
};

/**
 * This exception is thrown when the user tries to launch an unknown command.
 */
class UnknownCommandException : public IRCException {
    public:
        UnknownCommandException(const std::string &command) : IRCException("421", ERR_UNKNOWN_COMMAND(command)) {}
};

/**
 * This exception is thrown when a colon is missing.
 */
class MissingColonException : public IRCException {
    public:
        MissingColonException(const std::string &command) : IRCException("488", ERR_MISSING_COLON(command)) {}
};

#endif