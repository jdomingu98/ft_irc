#ifndef USER_HPP
# define USER_HPP

# include "libsUtils.hpp"
# include "Channel.hpp"
#include "Server.hpp"

# define MAX_CHANNELS 10

class Channel;

/**
 * A class that represents an user.
 */
class User {
    private:
        int         _fd;
        bool        _passwordChecked;
        bool        _registered;
        std::string             _username;
        std::string             _hostname;
        std::string             _serverName;
        std::string             _realName;
        std::string             _nickname;
        std::vector<Channel>    _channels;

        std::vector<Channel>::const_iterator findChannel(std::string channelName) const;
        std::vector<Channel>::iterator findChannel(std::string channelName);
        
    public:
        // Constructors and destructors
        User(int fd);
        ~User();

        // Getters
        int getFd() const;
        std::string getNickname() const;
        bool isPasswordChecked() const;
        bool isUserInMaxChannels() const;
        bool isAlreadyInChannel(std::string channelName) const;
        bool isRegistered() const;

        // Setters
        void setUsername(const std::string& username);
        void setHostname(const std::string& hostname);
        void setServerName(const std::string& serverName);
        void setRealName(const std::string& realName);
        void setNickname(const std::string& nickname);
        void setPassword(const std::string& password);

        // Operations
        void checkPassword();
        void makeRegistration(Server &server);
        bool canRegister();
        void joinChannel(Channel channel);
        void leaveChannel(std::string channelName);
};

#endif
