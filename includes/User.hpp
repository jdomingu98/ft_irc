#ifndef USER_HPP
# define USER_HPP

# include "Server.hpp"

# define MAX_CHANNELS 10

class Channel;

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

        // Less than operator
        bool operator<(const User& other) const;

        // Getters
        int getFd() const;
        std::string getNickname() const;
        std::string getUsername() const;
        std::string getHostname() const;
        bool isUserInMaxChannels() const;
        bool isOnChannel(const std::string &channelName) const;
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
        void removeChannel(const std::string &channelName);

        /**
         * This function aims to broadcast a message to all the users in the channel.
         * 
         * @param recipientUsers The users who will receive the message.
         * @param message The message to broadcast.
         */
        template <typename T>
        void User::broadcastToChannel(const T &recipientUsers, const std::string message) const {
            for (typename T::iterator it = recipientUsers.begin(); it != recipientUsers.end(); it++)
                Server::getInstance().sendMessage((*it)->getFd(), CMD_MSG(_nickname, _username, _hostname, message));
        }
};

#endif