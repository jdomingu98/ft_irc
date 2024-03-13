#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <iostream>
# include <cstdlib>

# include <arpa/inet.h>
# include <netdb.h> // gethostbyname
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>

# include <vector>
# include <sstream>

# include "utils.hpp"

// =================================================================================

# define SUCCESS 0
# define EXIT 1

# define INVALID_ARGS "[ERROR] Invalid args.\nUsage: ./ircserv <port> <password>"

# define PORT_OUT_OF_RANGE_ERR "[ERROR] Port out of range."

# define SOCKET_EXPT "[ERROR] Unable to open server socket."
# define BIND_EXPT "[ERROR] Unable to link server socket."
# define LISTEN_EXPT "[ERROR] unable to start listening on server socket."
# define POLL_EXPT "[ERROR] Unexpected failure on poll function."
# define ACCEPT_EXPT "[ERROR] Unable to accept connection."
# define REVENTS_EXPT "[ERROR] Poll revents value different from POLLIN."
# define RECV_EXPT "[ERROR] Unable to receive message."
# define SEND_EXPT "[ERROR] Unable to send message."

# define INVALID_COMMAND "[ERROR] Invalid command sent to server socket." //???

# define AUTH_ERR "[ERROR] Unauthorized.\nPlease send connection password and set your nickname and username."
# define INVALID_PASSWORD "[ERROR] Password provided doesn't match server password."

# define NOT_UQ_NICK_ERR "[ERROR] Nickname already in use."

# define MISSING_PARAMS_ERR "[ERROR] Missing parameters in command."

// ========================================= IRC COMMAND MESSAGE ERRORS =========================================

# define ERR_NEED_MORE_PARAMS(command) (command) " :Not enough parameters"
# define ERR_ALREADY_REGISTRED ":You may not reregister"

# define ERR_NO_NICKNAME_GIVEN ":No nickname given"
# define ERR_ERRONEUS_NICKNAME(nickname) (nickname) " :Erroneous nickname"
# define ERR_NICKNAME_IN_USE(nickname) (nickname) " :Nickname is already in use"
# define ERR_NICK_COLLISION(nickname) (nickname) " :Nickname collision KILL"

#endif