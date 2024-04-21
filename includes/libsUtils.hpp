#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <algorithm>
# include <cerrno>
# include <csignal>
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <map>
# include <set>
# include <sstream>
# include <string>
# include <vector>
# include <unistd.h>

# include "Channel.hpp"
# include "Logger.hpp"
# include "User.hpp"

# include "exceptions.hpp"
# include "IgnoreCommandException.hpp"

// =================================================================================

# define SUCCESS 0
# define EXIT 1

# define NONE ""

# define DEFAULT_PORT "6666"
# define DEFAULT_PASS "1234"

// ========================================= IRC SERVER ERROR MESSAGES =========================================
# define INVALID_ARGS "[ERROR] Invalid args.\nUsage: ./ircserv <port> <password>"

# define PORT_OUT_OF_RANGE_ERR "[ERROR] Port out of range."

# define WELCOME_MSG "Welcome to the ft_messenger server! Please enter your password: "

# define SOCKET_EXPT "[ERROR] Unable to open server socket."
# define REUSE_ADDR_EXPT "[ERROR] Failed to set SO_REUSEADDR option on server"
# define FCNTL_EXPT "[ERROR] Unable to set server socket as non-blocking."
# define BIND_EXPT "[ERROR] Unable to link server socket."
# define LISTEN_EXPT "[ERROR] unable to start listening on server socket."
# define POLL_EXPT "[ERROR] Unexpected failure on poll function."
# define ACCEPT_EXPT "[ERROR] Unable to accept connection."
# define REVENTS_EXPT "[ERROR] Poll revents value different from POLLIN."
# define RECV_EXPT "[ERROR] Unable to receive message."
# define SEND_EXPT "[ERROR] Unable to send message."

# define CODE_MSG(errorCode, nickname, errorMsg) ":irc.ft_messenger.net " + (errorCode) +  " " + (nickname) + " " + (errorMsg) + "."

//RPL_XXX -> Reply messages (Command Response)

# define RPL_TOPIC(channel, topic) (channel) + " :" + (topic)
# define RPL_TOPIC_CODE "332"

# define RPL_NO_TOPIC(channel) (channel) + " :No topic is set"
# define RPL_NO_TOPIC_CODE "331"

# define RPL_INVITING(channel, nickname) (channel) + " " + (nickname)
# define RPL_INVITING_CODE "341"

/*# define RPL_AWAY(nickname, awayMessage) (nickname) + " :" + (awayMessage)
# define RPL_AWAY_CODE "301"*/

/*# define RPL_CHANNEL_MODE_IS(channel, mode, modeParams) (channel) + " " + (mode) + " " + (modeParams)
# define RPL_CHANNEL_MODE_IS_CODE "324"*/

# define RPL_END_OF_NAMES(channel) (channel) + " :End of NAMES list."
# define RPL_END_OF_NAMES_CODE "366"

# define RPL_NAMES_REPLY_CODE "353"

# define USER_ID(nickname, username, hostname) ":" + (nickname) + "!" + (username) + "@" + (hostname)

# define JOIN_MSG(nickname, username, hostname, channelName) USER_ID(nickname, username, hostname) + " JOIN :" + (channelName)
# define PART_MSG(nickname, username, hostname, channelName) USER_ID(nickname, username, hostname) + " PART " + (channelName)
# define QUIT_MSG(nickname, username, hostname, message) USER_ID(nickname, username, hostname) + " QUIT :" + (message)
# define KICK_MSG(nickname, username, hostname, channelName, kickedUser, comment) USER_ID(nickname, username, hostname) + " KICK " + (channelName) + " " + (kickedUser) + " :" + (comment)
# define TOPIC_MSG(nickname, username, hostname, channelName, topic) USER_ID(nickname, username, hostname) + " TOPIC " + (channelName) + " " + (topic)
# define PRIVMSG_MSG(nickname, username, hostname, destination, message) USER_ID(nickname, username, hostname) + " PRIVMSG " + (destination) + " :" + (message)

std::vector<std::string> split(const std::string &s, char delim);

bool isNumber(const std::string& s);

const std::string &rplNamesReply(const std::string &nickname, const Channel &channel);

#endif