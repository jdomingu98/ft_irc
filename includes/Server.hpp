#ifndef SERVER_HPP
# define SERVER_HPP

# include "libsUtils.hpp"
# include "ServerException.hpp"

# define BUFFER_SIZE 1024
# define MAX_CLIENTS 30

class Server {

    private:
        uint16_t            _port;
        std::string         _password;
        int                 _socketFd;
        struct sockaddr_in  _serverAddr;
        struct pollfd       _fds[MAX_CLIENTS];

        bool isValidPort(const std::string port);
        void initServer();
        void listenClients();
        void handleNewConnection(int numFds);
        void handleExistingConnection(int fd);

    public:
        Server(const std::string port, const std::string password);
        ~Server();
};

#endif