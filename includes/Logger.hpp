#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <iostream>
# include <string>

class Logger {
    private:
        Logger(void);
        ~Logger(void);

	static const bool _debugMode = true;

    public:
        static void debug(std::string message);
};

#endif
