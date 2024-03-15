#ifndef SERVER_HPP
# define SERVER_HPP

# include "ICommand.hpp"
# include "CommandParser.hpp"

# include "User.hpp"

# include "libsUtils.hpp"

# define MIN_PORT 1
# define MAX_PORT 65535

# define BUFFER_SIZE 512
# define MAX_CLIENTS 42

/**
 * A class that represents the server.
 */
class Server {

    private:
        uint16_t            _port;
        std::string         _password;
        int                 _socketFd;
        struct sockaddr_in  _serverAddr;
        struct pollfd       _fds[MAX_CLIENTS];
        std::vector<User>   _users;

        bool isValidPort(const std::string port);
        void initServer();
        void listenClients();
        void handleNewConnection(int numFds);
        void handleExistingConnection(int fd);
        void closeConnections();

    public:
        Server(const std::string port, const std::string password);
        ~Server();

        bool isValidPassword(const std::string& password);
        User &getUserByFd(int fd);
        bool isNicknameInUse(const std::string& nickname);
        bool userHasCheckedPassword(int fd);
        void sendMessage(int clientFd, const std::string& message);
        void removeUser(int fd);
};

#endif