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

# include "Logger.hpp"

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

# define USER_ALREADY_IN_CHANNEL_ERR "[ERROR] User already in channel."
# define CHANNEL_ALREADY_ADDED_ERR "[ERROR] Channel already added."

//RPL_XXX -> Reply messages (Command Response)

# define RESPONSE_MSG(errorCode, nickname, errorMsg) ":irc.ft_messenger.net " + (errorCode) +  " " + (nickname) + " " + (errorMsg) + "."

# define RPL_TOPIC(nickname, username, hostname, channel, topic) USER_ID(nickname, username, hostname) + " " + (channel) + " :" + (topic)
# define RPL_NO_TOPIC(nickname, username, hostname, channel) USER_ID(nickname, username, hostname) + " " + (channel) + " :No topic is set"
# define RPL_INVITING(nickname, username, hostname, channel) USER_ID(nickname, username, hostname) + " " + (channel) + " " + (nickname)
// # define RPL_CHANNEL_MODE_IS(nickname, username, hostname, channel, mode, modeParams) USER_ID(nickname, username, hostname) + " " + (channel) + " " + (mode) + " " + (modeParams)
# define RPL_END_OF_NAMES(nickname, usermane, hostname, channel) USER_ID(nickname, username, hostname) + " " + (channel) + " :End of NAMES list."


# define CMD_MSG(nickname, username, hostname, message) USER_ID(nickname, username, hostname) + (message)
# define USER_ID(nickname, username, hostname) ":" + (nickname) + "!" + (username) + "@" + (hostname)

# define JOIN_MSG(channelName) " JOIN " + (channelName)
# define PART_MSG(channelName) " PART " + (channelName)
# define QUIT_MSG(message) " QUIT :" + (message)
# define KICK_MSG(channelName, kickedUser, comment) " KICK " + (channelName) + " " + (kickedUser) + " :" + (comment)
# define TOPIC_MSG(channelName, topic) " TOPIC " + (channelName) + " " + (topic)
# define PRIVMSG_MSG(destination, message) " PRIVMSG " + (destination) + " :" + (message)
# define INVITE_MSG(invitedUser, channel) " INVITE " + (invitedUser) + " " + (channel)

std::vector<std::string> split(const std::string &s, char delim);

bool isNumber(const std::string& s);

#endif