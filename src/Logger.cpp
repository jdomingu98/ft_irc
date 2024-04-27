#include "Logger.hpp"

Logger::Logger(void) {}

Logger::~Logger(void) {}

void Logger::debug(std::string message) {
    if (Logger::_debugMode)
        std::cout << "[DEBUG] " << message << std::endl;
}