#include "Server.hpp"

/**
 * This function aims to validate the port number.
 * A valid port number is between 1 and 65535.
 * 
 * @param port The port number to validate.
 * @return `true` if the port is valid, `false` otherwise.
 */
bool Server::isValidPort(const std::string port) {
    for (size_t i = 0; i < port.length(); i++){
        if (!std::isdigit(port[i]))
            return false;
    }
    int portNum = std::atoi(port.c_str());
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
    if (!this->isValidPort(port))
        throw ServerException(PORT_OUT_OF_RANGE_ERR);
    _port = std::atoi(port.c_str());
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
        0            // Let system decide the best protocol (SOCK_STREAM => TCP)
    );

    if (this->_socketFd < 0) {
        throw ServerException(SOCKET_EXPT);
    }

    // Config server address and port
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
    // htons: Converts host format port to network format port.
    this->_serverAddr.sin_port = htons(this->_port);

    // Binding the server socket
    if (bind(this->_socketFd, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr)) < 0) {
        throw ServerException(BIND_EXPT);
    }

    // Listen to incoming connections
    if (listen(this->_socketFd, MAX_CLIENTS) < 0) {
        throw ServerException(LISTEN_EXPT);
    }

    // Configure the first element of the pollfd structure array for the server socket
    this->_fds[0].fd = this->_socketFd;
    this->_fds[0].events = POLLIN;
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
    int num_fds = 1;
    while (true) {
        if (poll(this->_fds, num_fds, -1) == -1)
            throw ServerException(POLL_EXPT);

        for (int i = 0; i < num_fds; i++) {
            if (this->_fds[i].revents == 0)
                continue;

            if (this->_fds[i].revents != POLLIN)
                throw ServerException(REVENTS_EXPT);

            if (this->_fds[i].fd == this->_socketFd) {
                this->handleNewConnection(num_fds);
                num_fds++;
            } else {
                this->handleExistingConnection(this->_fds[i].fd);
            }
        }
    }
}

/**
 * This function aims to handle a new connection.
 * It accepts a new connection and adds the new socket to the array of poll_fds.
 * 
 * @param num_fds The number of file descriptors.
 * 
 * @throws `ServerException` if the server can't accept a new connection.
 */
void Server::handleNewConnection(int num_fds) {
    
    // Accept a new connection
    socklen_t size = sizeof(this->_serverAddr);
    int client_socket = accept(this->_socketFd, (struct sockaddr*)&this->_serverAddr, &size);

    if (client_socket < 0)
        throw ServerException(ACCEPT_EXPT);

    this->users.push_back(User(client_socket));
    // Add new socket to poll_fds array
    this->_fds[num_fds].fd = client_socket;
    this->_fds[num_fds].events = POLLIN;
}

/**
 * This function aims to handle an existing connection.
 * 
 * It receives a message from the client and sends a response.
 * 
 * @throws `ServerException` if the server can't receive a message or the server can't send a message.
 */
void Server::handleExistingConnection(int fd) {
    char buffer[BUFFER_SIZE];
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;

    int readBytes = recv(fd, buffer, BUFFER_SIZE, 0);
    if (readBytes < 0)
        throw ServerException(RECV_EXPT);
    buffer[readBytes] = 0;

    std::cout << "Client: " << buffer << "..." << std::endl;

    if (buffer[0] == '\0')
        return;

    std::string serverMessage = "Message received";
    try {
        ICommand* command = CommandParser::parse(std::string(buffer, readBytes));
        command->execute(*this, fd);
    } catch (CommandException& e) {
        serverMessage = "[COMMAND] ";
        serverMessage += e.what();
    } catch (ParserException& e) {
        serverMessage = "[PARSER] ";
        serverMessage += e.what();
    }
    serverMessage += "\n";
    if (send(fd, serverMessage.c_str(), serverMessage.size(), MSG_NOSIGNAL) < 0)
        throw ServerException(SEND_EXPT);
}

/**
 * This function aims to validate the password provided by the client.
 * 
 * @param password The password provided by the client.
 * @return `true` if the password is valid, `false` otherwise.
 */
bool Server::isValidPassword(const std::string& password) {
    return password == this->_password;
}

/**
 * This function aims to get the user by the file descriptor.
 * 
 * @param fd The file descriptor of the user.
 * @return The user with the file descriptor.
 */
User &Server::getUserByFd(int fd) {
    for (size_t i = 0; i < this->users.size(); i++) {
        if (this->users[i].getFd() == fd)
            return this->users[i];
    }
    throw ServerException("USER_NOT_FOUND_ERR");
}

/**
 * This function aims to check if a nickname is already in use.
 * 
 * @param nickname The nickname to check.
 * @return `true` if the nickname is already in use, `false` otherwise.
 */
bool Server::isNicknameInUse(const std::string& nickname) {
    for (size_t i = 0; i < this->users.size(); i++) {
        if (this->users[i].getNickname() == nickname)
            return true;
    }
    return false;
}