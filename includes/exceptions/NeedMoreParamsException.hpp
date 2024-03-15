
#ifndef NEED_MORE_PARAMS_EXCEPTION_HPP
# define NEED_MORE_PARAMS_EXCEPTION_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a command is missing parameters.
*/
class NeedMoreParamsException : public IRCException {
    public:
        NeedMoreParamsException(const std::string command) : IRCException("461", command + " :Not enough parameters") {}
        ~NeedMoreParamsException() throw() {}
};

#endif
