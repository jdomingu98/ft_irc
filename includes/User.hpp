#ifndef USER_HPP
# define USER_HPP

# include "libsUtils.hpp"

/**
 * A class that represents an user.
 */
class User {
    private:
        int _fd;
        bool _passwordChecked;
        std::string _username;
        std::string _hostname;
        std::string _serverName;
        std::string _realName;
        std::string _nickname;
        
    public:
        // Constructors and destructors
        User(int fd);
        ~User();

        // Getters
        int getFd() const;
        std::string getNickname() const;
        bool isPasswordChecked() const;

        // Setters
        void setUsername(const std::string& username);
        void setHostname(const std::string& hostname);
        void setServerName(const std::string& serverName);
        void setRealName(const std::string& realName);
        void setNickname(const std::string& nickname);

        // Operations
        void checkPassword();
};

#endif
