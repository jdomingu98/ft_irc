#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <iostream>
# include <string>

/**
 * A class that is responsible for logging messages.
 */
class Logger {
    private:
        Logger(void);
        ~Logger(void);

	static const bool _debugMode = true;

    public:
        static void debug(std::string message);
};

#endif