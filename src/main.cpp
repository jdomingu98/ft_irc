#include "libsUtils.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << INVALID_ARGS << std::endl;
        return EXIT;
    }
    // Check if the port is valid
    //Server server = Server(std::atoll(argv[1]), argv[2]);
    
    return SUCCESS;
}
