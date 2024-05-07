#include "Server.hpp"

/**
 * The main function.
 * B================D----3
 *
 * First it validates the arguments.
 * Then it creates a server and starts listening for incoming connections.
 * 
 * @param argc The number of arguments.
 * @param argv The arguments.
 * 
 * @throws `ServerException` if the server can't be created.
 * @return `0` if the program ends successfully, `1` otherwise.
 */
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << INVALID_ARGS << std::endl;
        return EXIT;
    }

    try {
        const std::string port = std::string(argv[1]);
        const std::string password = std::string(argv[2]);
        Server::init(port, password);
    } catch (ServerException &e) {
        std::cerr << e.what() << '\n';
    } catch (IRCException &e) {
        std::cerr << e.what() << '\n';
    }
    Server::delete();
    return SUCCESS;
}