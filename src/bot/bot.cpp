#include "GlaskBot.hpp"
#include <cstdlib>

/**
 * Validate the arguments. If the arguments are invalid, an exception is thrown.
 * 
 * @param argc The number of arguments
 * @param argv The arguments
 */
void validateArgs(int argc, char *argv[]) {
	if (argc != 4 && argc != 3)
		throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <hostname> <port> [<password>]");

	std::string portStr = argv[2];
	if (portStr.find_first_not_of("0123456789") != std::string::npos)
		throw std::invalid_argument("Invalid port number");
}

/**
 * Main function
 * 
 * @param argc The number of arguments
 * @param argv The arguments
 * @return int The exit code
 */
int main(int argc , char *argv[]) {
	try {
		validateArgs(argc, argv);
		std::string hostname = argv[1];
		std::string portStr = argv[2];
		std::string password = argc == 4 ? argv[3] : "";
		int port = std::atoi(portStr.c_str());
		GlaskBot c(hostname, port, password);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
    return 0;
}

