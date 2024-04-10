#include "Server.hpp"

Server *Server::_server = NULL;

/**
 * This function aims to validate the port number.
 * A valid port number is between 1 and 65535.
 * 
 * @param port The port number to validate.
 * @return `true` if the port is valid, `false` otherwise.
 */
bool Server::isValidPort(const std::string &port) const {
    for (size_t i = 0; i < port.length(); i++) {
        if (!std::isdigit(port[i]))
            return false;
    }
    int portNum = std::atoi(port.c_str());
    return portNum >= MIN_PORT && portNum <= MAX_PORT;
}

/**
 * Server default constructor.
 * 
 * @param port The port number to listen for incoming connections.
 * @param password The password to authenticate the clients.
 * 
 * @throws `ServerException` if the port is out of range.
 */
Server::Server(const std::string port, const std::string password) : _password(password), _signalReceived(false) {
    if (!this->isValidPort(port))
        throw ServerException(PORT_OUT_OF_RANGE_ERR);
    _port = std::atoi(port.c_str());
    this->initServer();
}

/**
 * Server destructor.
 * 
 * It closes the server socket and all the client sockets.
 */
Server::~Server() {
    this->closeConnections();
}

/**
 * This function aims to initialize the server.
 * 
 * @param port The port number to listen for incoming connections.
 * @param password The password to authenticate the clients.
 *
 */
void Server::init(std::string port, std::string password) {
    Server::_server = new Server(port, password);
    signal(SIGINT, &signalHandler);
    signal(SIGQUIT, &signalHandler);
    Server::_server->listenClients();
}

/**
 * This function aims to get the instance of the server.
 * 
 * @return The instance of the server.
 */
Server &Server::getInstance() {
    if (Server::_server == NULL)
        Server::_server = new Server(DEFAULT_PORT, DEFAULT_PASS);
    return *Server::_server;
}

/**
 * This function aims to handle the signals `Ctrl+C` + `Ctrl+\\`.
 * 
 * @param signal The signal received.
 */
void signalHandler(int signal) {
    (void) signal;
    std::cout << "\b\b\033[K";
    Logger::debug("Signal Received!!");
    Logger::debug("Stopping the server...");
    Server::getInstance().setSignalReceived();
}

/**
 * This function aims to close all the connections.
 */
void Server::closeConnections() {
    for (size_t i = 0; i < this->_users.size(); i++)
        close(this->_users[i].getFd());
    std::vector<User>().swap(this->_users);

    if (this->_socketFd != -1)
        close(this->_socketFd);
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
        AF_INET,        // IPv4
        SOCK_STREAM,    // Stream socket
        0               // Let system decide the best protocol (SOCK_STREAM => TCP)
    );

    if (this->_socketFd < 0)
        throw ServerException(SOCKET_EXPT);

    // Config server address and port
    this->_serverAddr.sin_family = AF_INET;
    this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
    // htons: Converts host format port to network format port.
    this->_serverAddr.sin_port = htons(this->_port);

    // set the socket option (SO_REUSEADDR) to reuse the address
    int enabled = 1;
    if (setsockopt(this->_socketFd, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(int)) < 0)
        throw ServerException(REUSE_ADDR_EXPT);

    // Setting the socket option for non-blocking socket (O_NONBLOCK)
    if (fcntl(this->_socketFd, F_SETFL, O_NONBLOCK) < 0)
        throw ServerException(FCNTL_EXPT);

    // Binding the server socket
    if (bind(this->_socketFd, (struct sockaddr*)&this->_serverAddr, sizeof(this->_serverAddr)) < 0)
        throw ServerException(BIND_EXPT);

    // Listen to incoming connections
    if (listen(this->_socketFd, MAX_CLIENTS) < 0)
        throw ServerException(LISTEN_EXPT);

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
 *  the server can't receive a message or
 *  the server can't send a message.
 */
void Server::listenClients() {
    int numFds = 1;
    
    while (!this->_signalReceived) {
        if (poll(this->_fds, numFds, -1) == -1 && !this->_signalReceived)
            throw ServerException(POLL_EXPT);

        for (int i = 0; i < numFds; i++) {
            if (this->_fds[i].revents == 0)
                continue;

            if (this->_fds[i].revents != POLLIN)
                throw ServerException(REVENTS_EXPT);

            if (this->_fds[i].fd == this->_socketFd) {
                this->handleNewConnection(numFds);
                numFds++;
            } else
                this->handleExistingConnection(this->_fds[i].fd);
        }
    }
    Logger::debug("Closing connections...");
    this->closeConnections();
}

/**
 * This function aims to handle a new connection.
 * It accepts a new connection and adds the new socket to the array of poll_fds.
 * 
 * @param numFds The number of file descriptors.
 * 
 * @throws `ServerException` if the server can't accept a new connection.
 */
void Server::handleNewConnection(int numFds) {
    
    // Accept a new connection
    socklen_t size = sizeof(this->_serverAddr);
    int clientSocket = accept(this->_socketFd, (struct sockaddr*) &this->_serverAddr, &size);

    if (clientSocket < 0)
        throw ServerException(ACCEPT_EXPT);
    
    // Setting the client socket option for non-blocking socket (O_NONBLOCK)
    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0)
        throw ServerException(FCNTL_EXPT);

    this->_users.push_back(User(clientSocket));
    // Add new socket to poll_fds array
    this->_fds[numFds].fd = clientSocket;
    this->_fds[numFds].events = POLLIN;

    this->sendMessage(clientSocket, WELCOME_MSG);
}

/**
 * This function aims to handle an existing connection.
 * 
 * It receives a message from the client and sends a response.
 * 
 * @throws `ServerException` if the server can't receive a message or the server can't send a message.
 */
void Server::handleExistingConnection(int clientFd) {
    char buffer[BUFFER_SIZE];
    for (size_t i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;

    int readBytes = recv(clientFd, buffer, BUFFER_SIZE, 0);
    if (readBytes < 0)
        throw ServerException(RECV_EXPT);
    buffer[readBytes] = 0;

    if (buffer[0] == '\0')
        return;
    Logger::debug("Mensaje del cliente: " + std::string(buffer, readBytes));
    User &client = getUserByFd(clientFd);
    try {
        ACommand* command = CommandParser::parse(std::string(buffer, readBytes));
        if (command->needsValidation() && !client.isRegistered())
            throw NotRegisteredException();
        command->execute(clientFd);
    } catch (IRCException& e) {
        this->sendExceptionMessage(clientFd, e);
    } catch (CommandNotFoundException &e) {
        this->sendMessage(clientFd, e.what());
    }
}

/**
 * This function validates if the user's password is the same as the server's password.
 * 
 * @param password The password provided by the client.
 * @return `true` if the password is valid, `false` otherwise.
 */
bool Server::isValidPassword(const std::string &password) const {
    return password == this->_password;
}

/**
 * This function sets to `true` the signal received flag
 */
void Server::setSignalReceived() {
    this->_signalReceived = true;
}

/**
 * This function aims to get the user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * @return The user with the file descriptor.
 */
User &Server::getUserByFd(int clientFd) {
    return *findUserByFd(clientFd);
}

/**
 * This function aims to get the user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * @return The user with the file descriptor.
 */
const User &Server::getUserByFd(int clientFd) const {
    return *findUserByFd(clientFd);
}

/**
 * This function aims to check if a nickname is already in use.
 * 
 * @param nickname The nickname to check.
 * @return `true` if the nickname is already in use, `false` otherwise.
 */
bool Server::isNicknameInUse(const std::string& nickname) const {
    std::vector<User>::const_iterator it = findUserByNickname(nickname);
    return it != this->_users.end();
}

/**
 * This function aims to get all the user information searching by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @throws `NoSuchNickException` if the user is not found.
 * 
 * @return The user object with all its information.
 */
User &Server::getUserByNickname(const std::string &nickname) {
    std::vector<User>::iterator it = this->findUserByNickname(nickname);
    if (it == this->_users.end())
        throw NoSuchNickException(nickname);
    return *it;
}

/**
 * This function aims to send a message to a client.
 * 
 * @param clientFd The file descriptor of the client.
 * @param message The message to send.
 * 
 * @throws `ServerException` if the server can't send the message.
*/
void Server::sendMessage(int clientFd, const std::string& message) const {
    std::string messageToSend = message + std::string("\r\n");
    if (send(clientFd, messageToSend.c_str(), messageToSend.size(), MSG_NOSIGNAL) < 0)
        throw ServerException(SEND_EXPT);
}

/**
 * This function aims to send an exception message to a client.
 * 
 * @param clientFd The file descriptor of the client.
 * @param e The exception to send.
 */
void Server::sendExceptionMessage(int clientFd, const IRCException &e) const {
    std::string clientNickname = getUserByFd(clientFd).getNickname();
    this->sendMessage(clientFd, ERROR_MSG(e.getErrorCode(), clientNickname.empty() ? "*" : clientNickname, e.what()));
}

/**
 * This function aims to remove a user from the server.
 * 
 * @param clientFd The file descriptor of the user to remove.
*/
void Server::removeUser(int fd) {
    std::vector<User>::iterator it = findUserByFd(fd);
    if (it != this->_users.end()) {
        close(it->getFd());
        this->_users.erase(it);
    }
}

/**
 * This function attempt to register a user.
 * 
 * @param clientFd The file descriptor of the user.
 */
void Server::attemptUserRegistration(int clientFd) {
    this->getUserByFd(clientFd).makeRegistration();
}

/**
 * This function aims to find a user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * 
 * @return The iterator to the user with the file descriptor.
 */
std::vector<User>::iterator Server::findUserByFd(int clientFd) {
    for (size_t i = 0; i < this->_users.size(); i++) {
        if (this->_users[i].getFd() == clientFd)
            return this->_users.begin() + i;
    }
    return this->_users.end();
}

/**
 * This function aims to find a user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * 
 * @return The iterator to the user with the file descriptor.
 */
std::vector<User>::const_iterator Server::findUserByFd(int clientFd) const {
    for (size_t i = 0; i < this->_users.size(); i++) {
        if (this->_users[i].getFd() == clientFd)
            return this->_users.begin() + i;
    }
    return this->_users.end();
}

/**
 * This function aims to find a user by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User>::iterator Server::findUserByNickname(const std::string &nickname) {
    for (size_t i = 0; i < this->_users.size(); i++) {
        if (this->_users[i].getNickname() == nickname)
            return this->_users.begin() + i;
    }
    return this->_users.end();
}

/**
 * This function aims to find a user by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User>::const_iterator Server::findUserByNickname(const std::string &nickname) const {
    for (size_t i = 0; i < this->_users.size(); i++) {
        if (this->_users[i].getNickname() == nickname)
            return this->_users.begin() + i;
    }
    return this->_users.end();
}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The iterator to the channel with the name.
 */
std::vector<Channel>::iterator Server::findChannel(const std::string &channelName) {
    for (size_t i = 0; i < this->_channels.size(); i++) {
        if (this->_channels[i].getName() == channelName)
            return this->_channels.begin() + i;
    }
    return this->_channels.end();
}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The iterator to the channel with the name.
 */
std::vector<Channel>::const_iterator Server::findChannel(const std::string &channelName) const {
    for (size_t i = 0; i < this->_channels.size(); i++) {
        if (this->_channels[i].getName() == channelName)
            return this->_channels.begin() + i;
    }
    return this->_channels.end();
}

/**
 * This function aims to add a channel to the server.
 * 
 * @param channel The channel to add.
 */
void Server::addChannel(Channel channel) {
    std::vector<Channel>::iterator it = findChannel(channel.getName());
    if (it != this->_channels.end())
        throw ServerException(CHANNEL_ALREADY_ADDED_ERR);
    this->_channels.push_back(channel);
}

/**
 * This function aims to get the channels of the server.
 * 
 * @return The channels of the server.
 */
std::vector<Channel> &Server::getChannels() {
    return this->_channels;
}

/**
 * This function aims to remove a channel from the server.
 * 
 * @param channelName The name of the channel to remove.
 */
void Server::removeChannel(std::string channelName) {
    std::vector<Channel>::iterator it = findChannel(channelName);
    if (it != this->_channels.end())
        this->_channels.erase(it);
}

/**
 * This function aims to get a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @throws `NoSuchChannelException` if the channel is not found.
 * 
 * @return The channel with the name.
 */
Channel &Server::getChannelByName(const std::string &channelName) {
    std::vector<Channel>::iterator it = findChannel(channelName);
    if (it == this->_channels.end())
        throw NoSuchChannelException(channelName);
    return *it;
}

/**
 * This function aims to check if a channel exists.
 * 
 * @param channelName The name of the channel.
 * 
 * @return `true` if the channel exists, `false` otherwise.
 */
bool Server::channelExists(const std::string &channelName) const {
    return findChannel(channelName) != this->_channels.end();
}
