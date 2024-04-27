#include "Logger.hpp"

/**
 * The logger constructor.
 */
Logger::Logger(void) {}

/**
 * The logger destructor.
 */
Logger::~Logger(void) {}

/**
 * Prints an error message if debug mode is active.
 * 
 * @param message The message to be printed.
 */
void Logger::debug(std::string message) {
    if (Logger::_debugMode)
        std::cout << "[DEBUG] " << message << std::endl;
}