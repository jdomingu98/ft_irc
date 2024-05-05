#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <fstream>
# include <map>
# include <sstream>
# include <string>
# include <sys/stat.h>
# include <sys/types.h>
# include <vector>

# include "User.hpp"

# define MAX_CHANNEL_NAME_LENGTH 20
# define NO_LIMIT 0
# define BELL_CHAR '\a'

# define DOWNLOAD_PATH(channel) "files/" + (channel) + "/"
# define FOLDER_PRIVILEGES 0777
class User;

/**
 * A class that represents the channels of the server.
*/
class Channel {
    private:
        std::string                 _name;
        std::string                 _password;
        std::vector<User *>         _operators;
        std::vector<User *>         _users;
        std::vector<std::string>    _inviteList;
        std::string                 _topic;
        int                         _limit;
        bool                        _passwordSet;
        std::map<std::string, std::vector<char> >  _files;

        // Modes
        bool    _inviteOnly;
        bool    _topicProtected;

        // Iterators
        std::vector<User *>::iterator         findUser(const std::string &nickname);
        std::vector<User *>::const_iterator   findUser(const std::string &nickname) const;
        std::vector<User *>::iterator         findOper(const std::string &nickname);
        std::vector<User *>::const_iterator   findOper(const std::string &nickname) const;

        // Other Operations
        bool checkName(std::string name) const;

    public:
        // Constructors and destructor
        Channel();
        Channel(const std::string name, User *user);
        Channel(const Channel &other);
        ~Channel();

        Channel &operator=(const Channel &other);

        std::string getName() const;
        void broadcast(const std::string &message);

        // User
        std::vector<User *> getUsers() const;
        void addUser(User *user);
        void removeUser(const std::string &nickname);

        // Oper
        void makeUserAnOper(std::string nickname);
        void makeOperAnUser(std::string nickname);
        bool isOper(const std::string &nickname) const;

        // Password
        std::string getPassword() const;
        bool isPasswordSet() const;
        void setPassword(const std::string &password);
        bool checkPassword(std::string password) const;
        void unsetPassword();

        // Topic
        std::string getTopic() const;
        void setTopic(std::string topic);
        bool isTopicProtected() const;
        void setTopicProtected(bool topicProtected);

        // Invite
        void inviteUser(const std::string &nickname);
        bool isUserInvited(std::string nickname) const;
        bool isInviteOnly() const;
        void setInviteOnly(bool inviteOnly);

        // Mode
        std::string getModes() const;
        std::string getModeParams() const;

        // Limit
        void setLimit(int limit);
        bool hasLimit() const;
        bool isFull() const;

        // Transfer file bonus
        void uploadFile(const std::string &path);
        void downloadFile(const std::string &filename);
};

#endif