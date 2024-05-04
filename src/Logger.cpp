#include "Logger.hpp"

/**
 * The logger constructor.
 */
Logger::Logger() {}

/**
 * The logger destructor.
 */
Logger::~Logger() {}

/**
 * Prints an error message if debug mode is active.
 * 
 * @param message The message to be printed.
 */
void Logger::debug(const std::string &message) {
    if (Logger::_debugMode)
        std::cout << "[DEBUG] " << message << '\n';
}