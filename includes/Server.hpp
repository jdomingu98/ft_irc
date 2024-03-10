#ifndef SERVER_HPP
# define SERVER_HPP

# include "libsUtils.hpp"

# define BUFFER_SIZE 1024

class Server {

    private:
        uint16_t            _port;
        std::string         _password;
        int                 _socketFd;
        struct sockaddr_in  _serverAddr;

        bool isValidPort(const char* port);
        void initServer();
        void listenClients();
        void handleNewConnection(int numFds);
        void handleExistingConnection();

    public:
        Server(const std::string port, const std::string password);
        ~Server();
};

#endif