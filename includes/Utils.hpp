#ifndef UTILS_HPP
# define UTILS_HPP

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
# include <ctime>

# include "Logger.hpp"

# include "exceptions.hpp"
# include "IgnoreCommandException.hpp"

// =================================================================================

# define SUCCESS 0
# define EXIT 1

# define NONE ""

# define DEFAULT_PORT "6666"
# define DEFAULT_PASS "1234"
# define DEFAULT_SERVER_VERSION "ft_messenger-v1.0.0"

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

# define RPL_TOPIC(nickname, username, hostname, channel, topic) USER_ID(nickname, username, hostname) + " " + (channel) + " :" + (topic)
# define RPL_NO_TOPIC(nickname, username, hostname, channel) USER_ID(nickname, username, hostname) + " " + (channel) + " :No topic is set"
# define RPL_INVITING(nickname, username, hostname, channel) USER_ID(nickname, username, hostname) + " " + (channel) + " " + (nickname)
// # define RPL_AWAY(nickname, username, hostname, awayMessage) USER_ID(nickname, username, hostname) + " " + (nickname) + " :" + (awayMessage)
// # define RPL_CHANNEL_MODE_IS(nickname, username, hostname, channel, mode, modeParams) USER_ID(nickname, username, hostname) + " " + (channel) + " " + (mode) + " " + (modeParams)
# define RPL_END_OF_NAMES(nickname, usermane, hostname, channel) USER_ID(nickname, username, hostname) + " " + (channel) + " :End of NAMES list."
# define RPL_WELCOME(nickname, username, hostname) std::string("Welcome to the Internet Relay Network ") + USER_ID(nickname, username, hostname)
# define RPL_YOURHOST(servername) "Your host is " + (servername) + ", running version " + (DEFAULT_SERVER_VERSION)
# define RPL_CREATED(date) "This server was create: " + (date)
# define RPL_MYINFO(servername, channelModes) (servername) + " " + (DEFAULT_SERVER_VERSION) + " Available user modes: " + ", Available channel modes: " + (channelModes)

# define ERROR_MSG(errorCode, nickname, errorMsg) ":irc.ft_messenger.net " + (errorCode) +  " " + (nickname) + " " + (errorMsg) + "."

# define USER_ID(nickname, username, hostname) ":" + (nickname) + "!" + (username) + "@" + (hostname)
# define JOIN_MSG(nickname, username, hostname, channelName) USER_ID(nickname, username, hostname) + " JOIN " + (channelName)
# define PART_MSG(nickname, username, hostname, channelName) USER_ID(nickname, username, hostname) + " PART " + (channelName)
# define QUIT_MSG(nickname, username, hostname, message) USER_ID(nickname, username, hostname) + " QUIT :" + (message)
# define KICK_MSG(nickname, username, hostname, channelName, kickedUser, comment) USER_ID(nickname, username, hostname) + " KICK " + (channelName) + " " + (kickedUser) + " :" + (comment)
# define TOPIC_MSG(nickname, username, hostname, channelName, topic) USER_ID(nickname, username, hostname) + " TOPIC " + (channelName) + " " + (topic)
# define PRIVMSG_MSG(nickname, username, hostname, destination, message) USER_ID(nickname, username, hostname) + " PRIVMSG " + (destination) + " :" + (message)
# define INVITE_MSG(nickname, username, hostname, invitedUser, channel) USER_ID(nickname, username, hostname) + " INVITE " + (invitedUser) + " " + (channel)
# define MODE_MSG(nickname, username, hostname, channel, flag, modeParams) USER_ID(nickname, username, hostname) + " MODE " + (channel) + " " + (flag) + " " + (modeParams)

class Utils {
    private:
        Utils();
        ~Utils();

    public:
        static std::vector<std::string> split(const std::string &s, char delim);
        static bool isNumber(const std::string& s);
        static std::string getCurrentDate();
};

#endif