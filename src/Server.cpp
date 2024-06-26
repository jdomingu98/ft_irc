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
    if (!isValidPort(port))
        throw ServerException(PORT_OUT_OF_RANGE_ERR);
    _port = std::atoi(port.c_str());
    generateDate();
    initServer();
}

/**
 * Server destructor.
 * 
 * It closes the server socket and all the client sockets.
 */
Server::~Server() {
    closeConnections();
    for (size_t i = 0; i < _users.size(); i++)
        delete _users[i];
    for (size_t i = 0; i < _channels.size(); i++)
        delete _channels[i];
}

void Server::deleteServer() {
    delete _server;
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
    for (size_t i = 0; i < _users.size(); i++)
        close(_users[i]->getFd());

    if (_socketFd != -1)
        close(_socketFd);
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
    _socketFd = socket(
        AF_INET,        // IPv4
        SOCK_STREAM,    // Stream socket
        0               // Let system decide the best protocol (SOCK_STREAM => TCP)
    );

    if (_socketFd < 0)
        throw ServerException(SOCKET_EXPT);

    // Config server address and port
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_addr.s_addr = INADDR_ANY;
    // htons: Converts host format port to network format port.
    _serverAddr.sin_port = htons(_port);

    // set the socket option (SO_REUSEADDR) to reuse the address
    int enabled = 1;
    if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(int)) < 0)
        throw ServerException(REUSE_ADDR_EXPT);

    // Setting the socket option for non-blocking socket (O_NONBLOCK)
    if (fcntl(_socketFd, F_SETFL, O_NONBLOCK) < 0)
        throw ServerException(FCNTL_EXPT);

    // Binding the server socket
    if (bind(_socketFd, (struct sockaddr*)&_serverAddr, sizeof(_serverAddr)) < 0)
        throw ServerException(BIND_EXPT);

    // Listen to incoming connections
    if (listen(_socketFd, MAX_CLIENTS) < 0)
        throw ServerException(LISTEN_EXPT);

    // Configure the first element of the pollfd structure array for the server socket
    struct pollfd socketPoll;
    
    socketPoll.fd = _socketFd;
    socketPoll.events = POLLIN;
    _fds.push_back(socketPoll);
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
    while (!_signalReceived) {
        if (poll(&_fds[0], _fds.size(), -1) == -1 && !_signalReceived)
            throw ServerException(POLL_EXPT);

        for (size_t i = 0; i < _fds.size(); i++) {
            if (_fds[i].revents == 0)
                continue;

            // Client disconnected
            if (_fds[i].revents & POLLHUP || _fds[i].revents & POLLERR || _fds[i].revents & POLLNVAL) {
                handleClientDisconnection(_fds[i].fd);
                continue;
            }

            if (_fds[i].revents != POLLIN)
                throw ServerException(REVENTS_EXPT);
            if (_fds[i].fd == _socketFd)
                handleNewConnection();
            else
                handleExistingConnection(_fds[i].fd);
        }
    }
    Logger::debug("Closing connections...");
}

/**
 * This function aims to handle a client disconnection.
 * It removes the user from all the channels and the server.
 * 
 * @param clientFd The file descriptor of the client.
 */
void Server::handleClientDisconnection(int clientFd) {
    std::vector<User *>::iterator userIt = findUserByFd(clientFd);

    if (userIt == _users.end())
        return;
    
    // Delete user from all channels where it joined
    std::vector<Channel *>::iterator channelIt = _channels.begin();
    while (channelIt != _channels.end() && !(*userIt)->isOnChannel((*channelIt)->getName()))
        ++channelIt;
    if (channelIt != _channels.end())
        (*channelIt)->removeUser((*userIt)->getNickname());

    // Erase possible input left by the user
    if (_inputBuffer.find(clientFd) != _inputBuffer.end())
        _inputBuffer.erase(clientFd);

    // Remove user from the server vector
    delete *userIt;
    _users.erase(userIt);

    // Close clientFd and remove it from the poll_fds array
    if (clientFd != -1) {
        std::vector<struct pollfd>::iterator pollIt = _fds.begin();
        while (pollIt != _fds.end() && pollIt->fd != clientFd)
            ++pollIt;
        if (pollIt != _fds.end()) {
            close(pollIt->fd);
            _fds.erase(pollIt);
        }
    }
}

/**
 * This function aims to handle a new connection.
 * It accepts a new connection and adds the new socket to the array of poll_fds.
 * 
 * @throws `ServerException` if the server can't accept a new connection.
 */
void Server::handleNewConnection() {
    
    // Accept a new connection
    socklen_t size = sizeof(_serverAddr);
    int clientSocket = accept(_socketFd, (struct sockaddr*) &_serverAddr, &size);

    if (clientSocket < 0)
        throw ServerException(ACCEPT_EXPT);
    
    // Setting the client socket option for non-blocking socket (O_NONBLOCK)
    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0)
        throw ServerException(FCNTL_EXPT);

    _users.push_back(new User(clientSocket));
    // Add new socket to poll_fds array
    struct pollfd newPoll;
    newPoll.fd = clientSocket;
    newPoll.events = POLLIN;
    _fds.push_back(newPoll);
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
    std::memset(buffer, '\0', BUFFER_SIZE);

    int readBytes = recv(clientFd, buffer, BUFFER_SIZE, 0);
    if (readBytes < 0) {
        handleClientDisconnection(clientFd);
        Logger::debug(RECV_EXPT);
    } else if (readBytes == 0) {
        QuitCommand quit("connection closed");
        quit.execute(clientFd);
        return;
    }
    
    buffer[readBytes] = '\0';

    if (!buffer[0])
        return;

    if (_inputBuffer.find(clientFd) == _inputBuffer.end())
        _inputBuffer[clientFd] = "";

    _inputBuffer[clientFd] += std::string(buffer, readBytes);

    Logger::debug("Mensaje del cliente: " + _inputBuffer[clientFd]);
    size_t pos;
    while ((pos = _inputBuffer[clientFd].find_first_of("\r\n")) != std::string::npos) {
        std::string message = _inputBuffer[clientFd].substr(0, pos);
        _inputBuffer[clientFd] = _inputBuffer[clientFd].substr(pos + 1);
        
        if (!_inputBuffer[clientFd].empty() && _inputBuffer[clientFd][0] == '\n') {
            _inputBuffer[clientFd] = _inputBuffer[clientFd].substr(1);
        }

        User *client = getUserByFd(clientFd);

        try {
            ACommand* command = CommandParser::parse(message, client);

            if (command->needsValidation() && !client->isRegistered())
                throw NotRegisteredException();
            command->execute(clientFd);
        } catch (PasswordMismatchException &e) {
            sendExceptionMessage(clientFd, e);
            handleClientDisconnection(clientFd);
        } catch (IRCException &e) {
            sendExceptionMessage(clientFd, e);
        } catch (IgnoreCommandException &e) {
            Logger::debug("Ignoring command");
        }
    }
}

/**
 * This function validates if the user's password is the same as the server's password.
 * 
 * @param password The password provided by the client.
 * @return `true` if the password is valid, `false` otherwise.
 */
bool Server::isValidPassword(const std::string &password) const {
    return password == _password;
}

/**
 * This function sets to `true` the signal received flag
 */
void Server::setSignalReceived() {
    _signalReceived = true;
}

/**
 * This function aims to get the user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * @return The user with the file descriptor.
 */
User *Server::getUserByFd(int clientFd) {
    return *findUserByFd(clientFd);
}

/**
 * This function aims to get the user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * @return The user with the file descriptor.
 */
const User *Server::getUserByFd(int clientFd) const {
    return *findUserByFd(clientFd);
}

/**
 * This function aims to check if a nickname is already in use.
 * 
 * @param nickname The nickname to check.
 * @return `true` if the nickname is already in use, `false` otherwise.
 */
bool Server::isNicknameInUse(const std::string& nickname) const {
    std::vector<User *>::const_iterator it = findUserByNickname(nickname);
    return it != _users.end();
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
User *Server::getUserByNickname(const std::string &nickname) {
    std::vector<User *>::iterator it = findUserByNickname(nickname);
    if (it == _users.end())
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
void Server::sendMessage(int clientFd, const std::string& message) {
    if (!isUserConnected(clientFd))
        return;

    int msgSignal = 0;
    std::string messageToSend = message + std::string("\r\n");
    
    // setsocketopt in Mac (+ 0 value on send function) to avoid sending signal SIGPIPE
    // Same behaviour in Linux with MSG_NOSIGNAL on send function
    #ifdef __APPLE__
        int enabled = 1;
        setsockopt(clientFd, SOL_SOCKET, SO_NOSIGPIPE, (void *) &enabled, sizeof(int));
    #else
        msgSignal = MSG_NOSIGNAL;
    #endif
    if (send(clientFd, messageToSend.c_str(), messageToSend.size(), msgSignal) < 0) {
        handleClientDisconnection(clientFd);
        Logger::debug(SEND_EXPT);
    }
}

/**
 * This function aims to send an exception message to a client.
 * 
 * @param clientFd The file descriptor of the client.
 * @param e The exception to send.
 */
void Server::sendExceptionMessage(int clientFd, const IRCException &e) {
    std::string clientNickname = getUserByFd(clientFd)->getNickname();
    sendMessage(clientFd, RESPONSE_MSG(e.getErrorCode(), clientNickname.empty() ? "*" : clientNickname, e.what()));
}

/**
 * This function aims to remove a user from the server.
 * 
 * @param clientFd The file descriptor of the user to remove.
*/
void Server::removeUser(int fd) {
    std::vector<User *>::iterator it = findUserByFd(fd);
    if (it != _users.end()) {
        close((*it)->getFd());
        _users.erase(it);
    }
}

/**
 * This function aims to get the users of the server.
 * 
 * @return The users of the server.
 */
std::vector<User *> Server::getUsers() {
    return _users;
}

/**
 * This function aims to find a user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * 
 * @return The iterator to the user with the file descriptor.
 */
std::vector<User *>::iterator Server::findUserByFd(int clientFd) {
    for (size_t i = 0; i < _users.size(); i++) {
        if (_users[i]->getFd() == clientFd)
            return _users.begin() + i;
    }
    return _users.end();
}

/**
 * This function aims to find a user by the file descriptor.
 * 
 * @param clientFd The file descriptor of the user.
 * 
 * @return The iterator to the user with the file descriptor.
 */
std::vector<User *>::const_iterator Server::findUserByFd(int clientFd) const {
    for (size_t i = 0; i < _users.size(); i++) {
        if (_users[i]->getFd() == clientFd)
            return _users.begin() + i;
    }
    return _users.end();
}

/**
 * This function aims to find a user by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User *>::iterator Server::findUserByNickname(const std::string &nickname) {
    for (size_t i = 0; i < _users.size(); i++) {
        if (_users[i]->getNickname() == nickname)
            return _users.begin() + i;
    }
    return _users.end();
}

/**
 * This function aims to find a user by the nickname.
 * 
 * @param nickname The nickname of the user.
 * 
 * @return The iterator to the user with the nickname.
 */
std::vector<User *>::const_iterator Server::findUserByNickname(const std::string &nickname) const {
    for (size_t i = 0; i < _users.size(); i++) {
        if (_users[i]->getNickname() == nickname)
            return _users.begin() + i;
    }
    return _users.end();
}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The iterator to the channel with the name.
 */
std::vector<Channel *>::iterator Server::findChannel(const std::string &channelName) {
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == channelName)
            return _channels.begin() + i;
    }
    return _channels.end();
}

/**
 * This function aims to find a channel by the name.
 * 
 * @param channelName The name of the channel.
 * 
 * @return The iterator to the channel with the name.
 */
std::vector<Channel *>::const_iterator Server::findChannel(const std::string &channelName) const {
    for (size_t i = 0; i < _channels.size(); i++) {
        if (_channels[i]->getName() == channelName)
            return _channels.begin() + i;
    }
    return _channels.end();
}

/**
 * This function aims to add a channel to the server.
 * 
 * @param channel The channel to add.
 */
void Server::addChannel(Channel *channel) {
    std::vector<Channel *>::iterator it = findChannel(channel->getName());
    if (it == _channels.end())
        _channels.push_back(channel);
}

/**
 * This function aims to get the channels of the server.
 * 
 * @return The channels of the server.
 */
std::vector<Channel *> &Server::getChannels() {
    return _channels;
}

/**
 * This function aims to remove a channel from the server.
 * 
 * @param channelName The name of the channel to remove.
 */
void Server::removeChannel(std::string channelName) {
    std::vector<Channel *>::iterator it = findChannel(channelName);
    if (it != _channels.end())
        _channels.erase(it);
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
Channel *Server::getChannelByName(const std::string &channelName) {
    std::vector<Channel *>::iterator it = findChannel(channelName);
    if (it == _channels.end())
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
    return findChannel(channelName) != _channels.end();
}

/**
 * This function aims to check if a user is connected.
 * 
 * @param clientFd The file descriptor of the user.
 * 
 * @return `true` if the user is connected, `false` otherwise.
 */
bool Server::isUserConnected(int clientFd) const {
    for (size_t i = 0; i < _fds.size(); i++) {
        if (_fds[i].fd == clientFd) {
            return true;
        }
    }
    return false;
}

/**
 * This function aims to generate the server creation date.
*/
void Server::generateDate() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    char buffer[100];

    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S UTC", now);
    _creationDate = std::string(buffer);
}

/**
 * Gets the current date.
 * 
 * @return The string with the current date.
 */
std::string Server::getCreationDate() const {
    return _creationDate;
}