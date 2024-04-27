#ifndef SERVER_HPP
# define SERVER_HPP

# include <arpa/inet.h>
# include <cerrno>
# include <csignal>
# include <cstdlib>
# include <cstring>
# include <fcntl.h>
# include <map>
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
# include <vector>

# include "ACommand.hpp"
# include "CommandParser.hpp"
# include "exceptions.hpp"
# include "IgnoreCommandException.hpp"
# include "Logger.hpp"
# include "QuitCommand.hpp"
# include "Responses.hpp"
# include "ServerException.hpp"

# define SUCCESS 0
# define EXIT 1

# define MIN_PORT 1
# define MAX_PORT 65535

# define DEFAULT_PORT "6667"
# define DEFAULT_PASS "1111"

# define BUFFER_SIZE 512
# define MAX_CLIENTS 42

# define NONE ""

# define INVALID_ARGS "[ERROR] Invalid args.\nUsage: ./ircserv <port> <password>"
# define PORT_OUT_OF_RANGE_ERR "[ERROR] Port out of range."

# define SOCKET_EXPT "[ERROR] Unable to open server socket."
# define REUSE_ADDR_EXPT "[ERROR] Failed to set SO_REUSEADDR option on server"
# define FCNTL_EXPT "[ERROR] Unable to set server socket as non-blocking."
# define BIND_EXPT "[ERROR] Unable to link server socket."
# define LISTEN_EXPT "[ERROR] unable to start listening on server socket."
# define POLL_EXPT "[ERROR] Unexpected failure on poll function."
# define ACCEPT_EXPT "[ERROR] Unable to accept connection."
# define REVENTS_EXPT "[ERROR] Poll revents value different from POLLIN."
# define RECV_EXPT "[ERROR] Unable to receive message."
# define SEND_EXPT "[ERROR] Unable to send message."

class Channel;

class User;

/**
 * A class that represents the server.
 */
class Server {

    private:
        uint16_t                    _port;
        std::string                 _password;
        int                         _socketFd;
        struct sockaddr_in          _serverAddr;
        struct pollfd               _fds[MAX_CLIENTS];
        int                         _numFds;
        std::map<int, std::string>  _inputBuffer;
        std::vector<User>           _users;
        std::vector<Channel>        _channels;

        // Singleton Pattern
        static Server               *_server;
        Server(const std::string port, const std::string password);

        // Signal Handler
        bool                        _signalReceived;

        // Server logic
        bool isValidPort(const std::string &port) const;
        void initServer();
        void listenClients();
        void handleNewConnection();
        void handleExistingConnection(int clientFd);

        // User Iterators
        std::vector<User>::iterator findUserByFd(int clientFd);
        std::vector<User>::const_iterator findUserByFd(int clientFd) const;
        std::vector<User>::iterator findUserByNickname(const std::string &nickname);
        std::vector<User>::const_iterator findUserByNickname(const std::string &nickname) const;


    public:
        ~Server();

        // Singleton Pattern
        static void init(std::string port, std::string password);
        static Server &getInstance();

        // User
        User        &getUserByFd(int clientFd);
        const User  &getUserByFd(int clientFd) const;
        User        &getUserByNickname(const std::string& nickname);
        bool        isNicknameInUse(const std::string& nickname) const;
        void        removeUser(int clientFd);
        void        attemptUserRegistration(int clientFd);

        // Channel
        std::vector<Channel> &getChannels();
        Channel &getChannelByName(const std::string &channelName);
        bool    channelExists(const std::string &channelName) const;
        void    addChannel(Channel channel);
        void    removeChannel(std::string channelName);

        // Disconnection
        bool    isUserConnected(int clientFd) const;
        void    handleClientDisconnection(int clientFd);
        void	closeConnections();

        // Other Operations
        void    sendMessage(int clientFd, const std::string& message) const;
        void    sendExceptionMessage(int clientFd, const IRCException &e) const;
        bool    isValidPassword(const std::string& password) const;
        void	setSignalReceived();

        // Channel Iterators
        std::vector<Channel>::iterator findChannel(const std::string &channelName);
        std::vector<Channel>::const_iterator findChannel(const std::string &channelName) const;
};

void signalHandler(int signal);

#endif