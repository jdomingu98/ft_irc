#ifndef UTILS_HPP
# define UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <sstream>
# include <vector>
# include <ctime>

# define DEFAULT_SERVER_VERSION "ft_messenger-v1.0.0"
// ========================================= IRC SERVER ERROR MESSAGES =========================================

# define RPL_WELCOME(nickname, username, hostname) std::string("Welcome to the Internet Relay Network ") + USER_ID(nickname, username, hostname)
# define RPL_YOURHOST(servername) "Your host is " + (servername) + ", running version " + (DEFAULT_SERVER_VERSION)
# define RPL_CREATED(date) "This server was create: " + (date)
# define RPL_MYINFO(servername, channelModes) (servername) + " " + (DEFAULT_SERVER_VERSION) + " Available user modes: " + ", Available channel modes: " + (channelModes)
# define USER_ID(nickname, username, hostname) ":" + (nickname) + "!" + (username) + "@" + (hostname)

# define JOIN_MSG(channelName) " JOIN " + (channelName)
# define PART_MSG(channelName) " PART " + (channelName)
# define QUIT_MSG(message) " QUIT :" + (message)
# define KICK_MSG(channelName, kickedUser, comment) " KICK " + (channelName) + " " + (kickedUser) + " :" + (comment)
# define TOPIC_MSG(channelName, topic) " TOPIC " + (channelName) + " " + (topic)
# define PRIVMSG_MSG(destination, message) " PRIVMSG " + (destination) + " :" + (message)
# define INVITE_MSG(invitedUser, channel) " INVITE " + (invitedUser) + " " + (channel)
# define MODE_MSG(nickname, username, hostname, channel, flag, modeParams) " MODE " + (channel) + " " + (flag) + " " + (modeParams)

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