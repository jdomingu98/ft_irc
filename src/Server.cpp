#include "Server.hpp"

/**
 * This function aims to validate the port number.
 * A valid port number is between 1 and 65535.
 * 
 * @param port The port number to validate.
 * @return `true` if the port is valid, `false` otherwise.
 */
bool isValidPort(const char* port) {
    for (char p : port) {
        if (!std::isdigit(p))
            return false;
    }
    int portNum = std::atoi(port);
    return portNum >= 1 && portNum <= 65535;
}

/**
 * Server default constructor.
 * 
 * @param port The port number to listen for incoming connections.
 * @param password The password to authenticate the clients.
 * 
 * @throws `ServerException` if the port is out of range.
 */
Server::Server(const std::string port, const std::string password): _password(password) {
    if (!isValidPort(argv[1]))
        throw new ServerException(PORT_OUT_OF_RANGE_ERR);
    _port = std::atoi(argv[1]);
    this->initServer();
    this->listenClients();
}

/**
 * Server destructor.
 * 
 * It closes the server socket and all the client sockets.
 */
Server::~Server() {

    if (this->_socketFd != -1) {
        close(this->_socketFd);
    }

    /*for (int clientSocket : clientSockets) {
        if (clientSocket != -1) {
            close(clientSocket);
        }
    }*/
}

/**
 * This function aims to create a server socket.
 * 
 * It creates a socket and binds it to the server address and port.
 * Then it starts listening for incoming connections.
 * 
 * @throws `ServerException` if the server socket can't be created, binded or started listening.
 */
void Server::initServer() {
    this->_socketFd = socket(
        AF_INET,      // IPv4
        SOCK_STREAM,  // Socket de flujo
        0,            // Let system decide the best protocol (SOCK_STREAM => TCP)
    );

    if (this->_socketFd < 0) {
        throw ServerException(INVALID_SOCKET);
    }

    // Config server address and port
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
    // htons: Converts host format port to network format port.
    this->_serverAddr.sin_port = htons(port);

    // Binding the server socket
    if (bind(this->_socketFd, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr)) < 0) {
        throw ServerException(INVALID_BIND);
    }

    // Listen to incoming connections
    if (listen(this->_socketFd, MAX_CLIENTS) < 0) {
        throw ServerException(INVALID_LISTEN);
    }

    // Configure the first element of the pollfd structure array for the server socket
    this->fds[0].fd = this->_socketFd;
    this->fds[0].events = POLLIN;
}

/**
 * This function aims to listen for incoming connections.
 * 
 * It uses the `poll` function to listen for incoming connections and messages from the clients.
 * 
 * @throws `ServerException` if the poll function fails,
 *  the server can't accept a new connection,
 *  the revents value is different from POLLIN,
 *  the server can't receive a message or the server can't send a message.
 */
void Server::listenClients() {
    int numFds = 1;
    while (true) {
        if (poll(this->fds, numFds, -1) == -1)
            throw ServerException(POLL_EXPT);

        for (int i = 0; i < numFds; i++) {
            if (this->fds[i].revents == 0)
                continue;

            if (this->fds[i].revents != POLLIN)
                throw ServerException(REVENTS_EXPT);

            if (this->fds[i].fd == this->_socketFd) {
                this->handleNewConnection(numFds);
                numFds++;
            } else {
                this->handleExistingConnection();
            }
        }
    }
}

/**
 * This function aims to handle a new connection.
 * It accepts a new connection and adds the new socket to the array of pollfds.
 * 
 * @param numFds The number of file descriptors.
 * 
 * @throws `ServerException` if the server can't accept a new connection.
 */
void Server::handleNewConnection(int numFds) {
    
    // Accept a new connection
    socklen_t size = sizeof(this->_serverAddr);
    int client_socket = accept(this->_socketFd, (struct sockaddr*)&this->_serverAddr, &size);

    if (client_socket < 0)
        throw ServerException(ACCEPT_EXPT);

    // Add new socket to pollfds array
    this->fds[numFds].fd = client_socket;
    this->fds[numFds].events = POLLIN;
}

/**
 * This function aims to handle an existing connection.
 * 
 * It receives a message from the client and sends a response.
 * 
 * @throws `ServerException` if the server can't receive a message or the server can't send a message.
 */
void Server::handleExistingConnection() {
    char buffer[BUFFER_SIZE];
    for (int i = 0; i < sizeof(buffer); i++)
        buffer[i] = 0;

    if (recv(this->fds[i].fd, buffer, BUFFER_SIZE, 0) < 0)
        throw ServerException(RECV_EXPT);

    std::cout << "Client: " << buffer << std::endl;

    std::string serverMessage = "Message received";
    if (send(this->fds[i].fd, serverMessage.c_str(), serverMessage.size(), MSG_NOSIGNAL) < 0)
        throw ServerException(SEND_EXPT);
}