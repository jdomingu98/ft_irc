#ifndef USER_HPP
# define USER_HPP

# include "libsUtils.hpp"
# include "Channel.hpp"
# include "Server.hpp"

# define MAX_CHANNELS 10

class Channel;
class Server;

/**
 * A class that represents an user.
 */
class User {
    private:
        int                     _fd;
        bool                    _registered;
        std::string             _username;
        std::string             _hostname;
        std::string             _serverName;
        std::string             _realName;
        std::string             _nickname;
        std::string             _password;
        std::vector<Channel>    _channels;

        // Iterators
        std::vector<Channel>::const_iterator findChannel(const std::string &channelName) const;
        std::vector<Channel>::iterator findChannel(const std::string &channelName);
        
    public:
        User(int fd);
        ~User();

        // Getters
        int getFd() const;
        std::string getNickname() const;
        std::string getUsername() const;
        std::string getHostname() const;
        bool isUserInMaxChannels() const;
        bool isOnChannel(std::string channelName) const;
        bool isRegistered() const;
        Channel *getChannelByName(std::string &channelName);

        // Setters
        void setUsername(const std::string& username);
        void setHostname(const std::string& hostname);
        void setServerName(const std::string& serverName);
        void setRealName(const std::string& realName);
        void setNickname(const std::string& nickname);
        void setPassword(const std::string& password);

        // Operations
        void makeRegistration();
        bool canRegister() const;
        void addChannel(Channel &channel);
        void sendPrivateMessageToUser(const User &destination, const std::string& message) const;
};

#endif
