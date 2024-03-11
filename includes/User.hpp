#ifndef USER_HPP
# define USER_HPP

# include "libsUtils.hpp"

class User {
    private:
        int _fd;
        bool _passwordChecked;
        std::string _username;
        std::string _hostname;
        std::string _serverName;
        std::string _realName;

    public:
      User(int fd);

      // Getters
      int getFd() const;
      bool isPasswordChecked() const;

      // Setters
      void setUsername(const std::string& username);
      void setHostname(const std::string& hostname);
      void setServerName(const std::string& serverName);
      void setRealName(const std::string& realName);

      // Operations
      void checkPassword();
};

#endif
