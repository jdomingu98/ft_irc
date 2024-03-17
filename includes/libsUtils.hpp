#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <cstdlib>
# include <iostream>
# include <sstream>
# include <algorithm>
# include <vector>

# include "utils.hpp"

// =================================================================================

# define SUCCESS 0
# define EXIT 1

# define INVALID_ARGS "[ERROR] Invalid args.\nUsage: ./ircserv <port> <password>"

# define PORT_OUT_OF_RANGE_ERR "[ERROR] Port out of range."

# define SOCKET_EXPT "[ERROR] Unable to open server socket."
# define BIND_EXPT "[ERROR] Unable to link server socket."
# define LISTEN_EXPT "[ERROR] unable to start listening on server socket."
# define POLL_EXPT "[ERROR] Unexpected failure on poll function."
# define ACCEPT_EXPT "[ERROR] Unable to accept connection."
# define REVENTS_EXPT "[ERROR] Poll revents value different from POLLIN."
# define RECV_EXPT "[ERROR] Unable to receive message."
# define SEND_EXPT "[ERROR] Unable to send message."

# define INVALID_COMMAND "[ERROR] Invalid command sent to server socket." //???

# define AUTH_ERR "[ERROR] Unauthorized.\nPlease send connection password and set your nickname and username."
# define INVALID_PASSWORD "[ERROR] Password provided doesn't match server password."
# define MISSING_PARAMS_ERR "[ERROR] Missing parameters."

# define USER_NOT_FOUND_ERR "[ERROR] User not found in list."

# define CHANNEL_ALREADY_ADDED_ERR "[ERROR] Channel already added."
# define USER_ALREADY_IN_CHANNEL_ERR "[ERROR] User already in channel."

// ========================================= IRC COMMAND ERROR MESSAGES =========================================

//RPL_XXX -> Reply messages (Command Response)

# define ERR_NEED_MORE_PARAMS(command) (command) " :Not enough parameters"
# define ERR_ALREADY_REGISTRED ":You may not reregister"

# define ERR_NO_NICKNAME_GIVEN ":No nickname given"
# define ERR_ERRONEUS_NICKNAME(nickname) (nickname) " :Erroneous nickname"
# define ERR_NICKNAME_IN_USE(nickname) (nickname) " :Nickname is already in use"
# define ERR_NICK_COLLISION(nickname) (nickname) " :Nickname collision KILL"

# define ERR_BANNED_FROM_CHAN(channel) (channel) " :Cannot join channel (+b)"
# define ERR_INVITE_ONLY_CHAN(channel) (channel) " :Cannot join channel (+i)"
# define ERR_BAD_CHANNEL_KEY(channel) (channel) " :Cannot join channel (+k)"
# define ERR_CHANNEL_IS_FULL(channel) (channel) " :Cannot join channel (+l)"
// # define ERR_BAD_CHAN_MASK ""
# define ERR_NO_SUCH_CHANNEL(channelName) (channelName) " :No such channel"
# define ERR_TOO_MANY_CHANNELS(channelName) (channelName) " :You have joined too many channels"
# define RPL_TOPIC(channel, topic) (channel) " :" (topic)

#define ERR_NOT_ON_CHANNEL(channel) (channel) " :You're not on that channel"

#define RPL_NO_TOPIC(channel) (channel) " :No topic is set"
#define ERR_CHAN_O_PRIVS_NEEDED(channel) (channel) " :You're not channel operator"

#define ERR_NO_SUCH_NICK(nickname) (nickname) " :No such nick/channel"
#define ERR_USER_ON_CHANNEL(nickname, channel) (nickname) " " (channel) " :is already on channel"
#define RPL_INVITING(channel, nickname) (channel) " " (nickname)
#define RPL_AWAY(nickname, awayMessage) (nickname) " :" (awayMessage)

#define ERR_NO_RECIPIENT(command) ":No recipient given " (command)
#define ERR_NO_TEXT_TO_SEND ":No text to send"
#define ERR_CANNOT_SEND_TO_CHAN(channel) (channel) " :Cannot send to channel"
#define ERR_NO_TOP_LEVEL(mask) (mask) " :No toplevel domain specified"
#define ERR_WILD_TOP_LEVEL(mask) (mask) " :Wildcard in toplevel domain"
#define ERR_TOO_MANY_TARGETS(target)  (target)" :Duplicate recipients. No message delivered"

#define RPL_CHANNEL_MODE_IS(channel, mode, modeParams) (channel) " " (mode) " " (modeParams)
#define ERR_KEYSET(channel) (channel) " :Channel key already set"
#define RPL_BAN_LIST (channe, banId) (channel) " " (banId)
#define RPL_END_OF_BAN_LIST(channel)  (channel) " :End of channel ban list"
#define ERR_UNKOWN_MODE (modeChar) (modeChar) " :is unknown mode char to me"
#define ERR_USERS_DONT_MATCH ":Cant change mode for other users"
#define ERR_U_MODE_IS(userModeString) (userModeString)
#define ERR_U_MODE_UNKNOWN_FLAG ":Unknown MODE flag"

#endif