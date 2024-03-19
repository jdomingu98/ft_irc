#include "Logger.hpp"

Logger::Logger(void) {}

Logger::~Logger(void) {}

void Logger::debug(std::string message) {
#ifdef DEBUG
    std::cout << "[DEBUG] " << message << std::endl;
#endif
}
