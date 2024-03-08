
#include "Server.hpp"

int ft_doRandomStaff(int port) {
    // Crear el socket del servVidor

    // AF_INET => IPv4
    // SOCK_STREAM -> Socket de flujo
    // 0 => Dejamos al sistema decidir el protocolo adecuado. SOCK_STREAM => TCP
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0) {
        // TODO: add to constants.
        std::cerr << INVALID_SOCKET << std::endl;
        return -1;
    }

    // Configurar la estructura del servidor
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // htons: convertir un puerto de formato de host al formato de red.
    server_addr.sin_port = htons(port);

    // Vincular el socket del servidor
    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        // TODO: add to constants.
        std::cerr << "Error al vincular el socket del servidor" << std::endl;
        return -1;
    }

    // Escuchar las conexiones entrantes
    if (listen(socket_fd, MAX_CLIENTS) < 0) {
        // TODO: add to constants.
        std::cerr << "Error al iniciar la escucha del socket del servidor" << std::endl;
        return -1;
    }


    struct pollfd fds[MAX_CLIENTS];
    int num_fds = 1;

    // Configurar el primer elemento de la matriz de estructuras pollfd para el socket del servidor
    fds[0].fd = socket_fd;
    fds[0].events = POLLIN;
    
    /****/

    // Bucle principal del servidor
    while (1) {
        if (poll(fds, num_fds, -1) == -1) {
            std::cerr << "Error en poll" << std::endl;
            return -1;
        }

        for (int i = 0; i < num_fds; i++) {
            if (fds[i].revents == 0)
                continue;

            if (fds[i].revents != POLLIN) {
                std::cerr << "Error! revents = " << fds[i].revents << std::endl;
                return -1;
            }

            if (fds[i].fd == socket_fd) {
                // Aceptar una nueva conexión
                socklen_t size = sizeof(server_addr);
                int client_socket = accept(socket_fd, (struct sockaddr*)&server_addr, &size);

                if (client_socket < 0) {
                    std::cerr << "Error al aceptar la conexión" << std::endl;
                    return -1;
                }

                // Agregar el nuevo socket al array de pollfds
                fds[num_fds].fd = client_socket;
                fds[num_fds].events = POLLIN;
                num_fds++;
            } else {
                char buffer[BUFFER_SIZE];
                memset(buffer, 0, sizeof(buffer));

                if (recv(fds[i].fd, buffer, BUFFER_SIZE, 0) < 0) {
                    std::cerr << "Error al recibir el mensaje" << std::endl;
                    return -1;
                }

                std::cout << "Cliente: " << buffer << std::endl;

                std::string server_message = "Mensaje recibido";
                if (send(fds[i].fd, server_message.c_str(), server_message.size(), MSG_NOSIGNAL) < 0) {
                    std::cerr << "Error al enviar el mensaje" << std::endl;
                    return -1;
                }
            }
        }
    }

    return 0;
}