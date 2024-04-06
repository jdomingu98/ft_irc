#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Server.hpp"

# include "libsUtils.hpp"

# define MAX_CHANNEL_NAME_LENGTH 20
# define NO_LIMIT -1
# define BELL_CHAR '\a'

class Server;

class User;

/**
 * A class that represents the channels of the server.
*/
class Channel {
    private:
        std::string                 _name;
        std::string                 _password;
        std::vector<User>           _users;
        std::vector<User>           _operators;
        std::vector<std::string>    _inviteList;
        std::string                 _topic;
        int                         _limit;
        bool                        _passwordSet;

        // modes
        bool    _inviteOnly;
        bool    _topicProtected;

        // Iterators
        std::vector<User>::iterator         findUser(const std::string &nickname);
        std::vector<User>::const_iterator   findUser(const std::string &nickname) const;
        std::vector<User>::iterator         findOper(const std::string &nickname);
        std::vector<User>::const_iterator   findOper(const std::string &nickname) const;

        // Other Operations
        bool checkChannelName(std::string name) const;

    public:
        // Constructors and destructor
        Channel(const std::string &name, const User &user);
        ~Channel();

        // Getters
        std::string         getName() const;
        std::string         getPassword() const;
        std::vector<User>   getUsers() const;
        std::vector<User>   getOperators() const;
        std::vector<User>   getAllUsers() const;
        std::string         getTopic() const;
        bool                isPasswordSet() const;

        // Setters
        void setTopic(std::string topic);

        // User
        void addUser(User user);
        void removeUser(std::string nickname);
        bool isUserInChannel(const std::string &nickname) const;

        // Oper
        void addOper(User user);
        void makeUserAnOper(std::string nickname);
        void makeOperAnUser(std::string nickname);
        bool isOper(const std::string &nickname) const;
        void BroadcastToChannel(const std::string &message, const std::string &nickname);

        // Invite
        void inviteUser(const std::string &nickname);
        bool isUserInvited(std::string nickname) const;

        // Modes
        bool isInviteOnly() const;
        void setInviteOnly(bool inviteOnly);
        bool isTopicProtected() const;
        void setTopicProtected(bool topicProtected);

        // Password
        void setPassword(const std::string &password);
        bool checkPassword(std::string password) const;
        void unsetPassword();

        // Limit
        void setLimit(int limit);
        bool hasLimit() const;
        bool isFull() const;
};

#endif