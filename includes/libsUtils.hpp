#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <cstdlib>
# include <iostream>
# include <sstream>
# include <algorithm>
# include <vector>

# include "utils.hpp"

#include "exceptions.hpp"

// =================================================================================

# define SUCCESS 0
# define EXIT 1

// ========================================= IRC SERVER ERROR MESSAGES =========================================
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

# define USER_NOT_FOUND_ERR "[ERROR] User not found in list."

# define CHANNEL_ALREADY_ADDED_ERR "[ERROR] Channel already added."
# define USER_ALREADY_IN_CHANNEL_ERR "[ERROR] User already in channel."
#endif