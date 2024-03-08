#include "Server.hpp"

Server::Server(uint16_t port, std::string password) : _port(std::atoi(port)), _password(password) {
    try {
        initServer();
    } catch (ServerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

Server::~Server() {
    
    // Cerrar el socket del servidor
    if (this->socket_fd != -1) {
        close(this->socket_fd);
    }

    // Cerrar todos los sockets de los clientes
    /*for (int clientSocket : clientSockets) {
        if (clientSocket != -1) {
            close(clientSocket);
        }
    }*/
}


/**
 * This function aims to create a server socket.
 */
void Server::initServer() {
    this->socket_fd = socket(
        AF_INET,      // IPv4
        SOCK_STREAM,  // Socket de flujo
        0,            // Let system decide the best protocol (SOCK_STREAM => TCP)
    );

    if (this->socket_fd < 0) {
        throw ServerException(INVALID_SOCKET);
    }

    // Config server address and port
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = INADDR_ANY;
    // htons: Converts host format port to network format port.
    this->server_addr.sin_port = htons(port);

    // Vincular el socket del servidor
    if (bind(this->socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw ServerException(INVALID_BIND);
    }

    // Escuchar las conexiones entrantes
    if (listen(socket_fd, MAX_CLIENTS) < 0) {
        throw ServerException(INVALID_LISTEN);
    }

    // Configurar el primer elemento de la matriz de estructuras pollfd para el socket del servidor
    this->fds[0].fd = socket_fd;
    this->fds[0].events = POLLIN;
}