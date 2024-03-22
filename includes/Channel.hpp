#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"

# include "ChannelException.hpp"

# include "libsUtils.hpp"

# define MAX_CHANNEL_NAME_LENGTH 20
# define NO_LIMIT -1
# define BELL_CHAR '\a'

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
        std::vector<std::string>    _banList;
        std::string         _topic;
        std::string         _modes;
        int                 _limit;
        bool                _passwordSet;

        bool checkChannelName(std::string name) const;
        std::vector<User>::iterator findUser(std::string nickname);
        std::vector<User>::iterator findOper(std::string nickname);
        bool isModesSet(std::string modesToCheck) const;
    
    public:
        //Constructors and destructor
        Channel(std::string name, User user);
        ~Channel();

        //Getters
        std::string getName() const;
        std::string getPassword() const;
        std::vector<User> getUsers() const;
        std::vector<User> getOperators() const;
        std::vector<User> getAllUsers() const;
        std::string getTopic() const;
        std::string getModes() const;
        bool isPasswordSet() const;


        //Setters
        void setPassword(std::string password);
        void setTopic(std::string topic);
        void changeMode(std::string modes);

        //Operations
        bool checkPassword(std::string password) const;
        bool isInviteOnly() const;
        bool isUserInvited(std::string nickname) const;
        bool isUserBanned(std::string nickname, std::string username, std::string hostname) const;
        bool hasLimit() const;
        bool isFull() const;
        void addUser(User user);
        void removeUser(std::string nickname);
        void removeOper(std::string nickname);
        void makeUserAnOper(std::string nickname);
        void makeOperAnUser(std::string nickname);
};

#endif