#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <sstream>
# include <vector>

// ========================================= IRC SERVER ERROR MESSAGES =========================================

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