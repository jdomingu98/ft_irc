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

# define DEFAULT_PORT "6667"
# define DEFAULT_PASS "1111"

// ========================================= IRC SERVER ERROR MESSAGES =========================================

# define INVALID_ARGS "[ERROR] Invalid args.\nUsage: ./ircserv <port> <password>"
# define PORT_OUT_OF_RANGE_ERR "[ERROR] Port out of range."

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