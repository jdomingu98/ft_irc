#include "GlaskBot.hpp"
#include <cstdlib>

int main(int argc , char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <hostname> <port>\n";
        return 1;
    }
     
    std::string hostname = argv[1];

    std::string portStr = argv[2];
    if (portStr.find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Invalid port number\n";
        return 1;
    }
    int port = std::atoi(portStr.c_str());
    // Connect to host
    GlaskBot c(hostname, port);
    return 0;
}