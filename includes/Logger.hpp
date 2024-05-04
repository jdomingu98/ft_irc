#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <iostream>
# include <string>

/**
 * A class that is responsible for logging messages.
 */
class Logger {
    private:
        Logger();
        ~Logger();

	static const bool _debugMode = true;

    public:
        static void debug(const std::string &message);
};

#endif