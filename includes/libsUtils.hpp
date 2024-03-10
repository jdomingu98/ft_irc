#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

// Libraries used in the project

# include <iostream>
# include <string> //-> Eliminar si no se usa algo especifico de std::string
# include <unistd.h> // close function to close sockets -> Search for alternatives
# include <cstdlib>

# include <arpa/inet.h>
# include <netdb.h> // gethostbyname
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>


// Consts definition

# define SUCCESS 0
# define EXIT 1

# define INVALID_ARGS "[ERROR] Invalid args.\n Usage: ./ircserv <port> <password>"

# define PORT_OUT_OF_RANGE_ERR "[ERROR] Port out of range."

# define SOCKET_EXPT "[ERROR] Unable to open server socket."
# define BIND_EXPT "[ERROR] Unable to link server socket."
# define LISTEN_EXPT "[ERROR] unable to start listening on server socket."
# define POLL_EXPT "[ERROR] Unexpected failure on poll function."
# define ACCEPT_EXPT "[ERROR] Unable to accept connection."
# define REVENTS_EXPT "[ERROR] Poll revents value different from POLLIN."
# define RECV_EXPT "[ERROR] Unable to receive message."
# define SEND_EXPT "[ERROR] Unable to send message."

# define INVALID_COMMAND "[ERROR] Invalid command sent to server socket."

# define AUTH_COMMAND_ERR "[ERROR] Sent password, nickname and username first to authenticate."

# define INVALID_PASSWORD "[ERROR] Password provided doesn't match server password."
# define NOT_UQ_NICK_ERR "[ERROR] Nickname already in use."


#endif
