#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <algorithm>
# include <cstdlib>
# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <unistd.h>

# include "Logger.hpp"

# include "exceptions.hpp"

# include "Server.hpp"

// =================================================================================

# define SUCCESS 0
# define EXIT 1

# define DEFAULT_PORT "6666"
# define DEFAULT_PASS "1234"

// ========================================= IRC SERVER ERROR MESSAGES =========================================
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

# define USER_ALREADY_IN_CHANNEL_ERR "[ERROR] User already in channel."
# define CHANNEL_ALREADY_ADDED_ERR "[ERROR] Channel already added."

//RPL_XXX -> Reply messages (Command Response)

# define RPL_TOPIC(channel, topic) (channel) + " :" + (topic)
# define RPL_NO_TOPIC(channel) (channel) + " :No topic is set"
# define RPL_INVITING(channel, nickname) (channel) + " " + (nickname)
// # define RPL_AWAY(nickname, awayMessage) (nickname) + " :" + (awayMessage)
// # define RPL_CHANNEL_MODE_IS(channel, mode, modeParams) (channel) + " " + (mode) + " " + (modeParams)

# define PART_MSG(nickname, username, hostname, channelName) ":" + nickname + "!" + username + "@" + hostname + " PART " + channelName
# define KICK_MSG(nickname, username, hostname, channelName, kickedUser, comment) ":" + nickname + "!" + username + "@" + hostname + " KICK " + channelName + " " + kickedUser + " :" + comment

std::string trim(const std::string& str);
std::vector<std::string> split(const std::string &s, char delim);
const std::string &join(const std::vector<std::string> &msg);
bool isColon(const std::vector<std::string> &msg);
bool isOnlySpaces(const std::vector<std::string> &msg);

#endif