#include "libsUtils.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << INVALID_ARGS << std::endl;
        return EXIT;
    }
    
    return SUCCESS;
}