#ifndef SERVER_HPP
# define SERVER_HPP

# include "libsUtils.hpp"
# include "exceptions/ServerException.hpp"
# include "parser/CommandParser.hpp"
# include "commands/ICommand.hpp"
# include "exceptions/CommandException.hpp"
# include "ParserException.hpp"
# include "User.hpp"

# define BUFFER_SIZE 1024
# define MAX_CLIENTS 30

class Server {

    private:
        uint16_t            _port;
        std::string         _password;
        int                 _socketFd;
        struct sockaddr_in  _serverAddr;
        struct pollfd       _fds[MAX_CLIENTS];
        std::vector<User>    users;

        bool isValidPort(const std::string port);
        void initServer();
        void listenClients();
        void handleNewConnection(int numFds);
        void handleExistingConnection(int fd);

    public:
        Server(const std::string port, const std::string password);
        ~Server();

        bool isValidPassword(const std::string& password);
        User &getUserByFd(int fd);
        bool isNicknameInUse(const std::string& nickname);
};

#endif