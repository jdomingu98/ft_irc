#ifndef NOT_REGISTERED_EXCEPTION_HPP
# define NOT_REGISTERED_EXCEPTION_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a command is given before the user is registered.
 */
class NotRegisteredException : public IRCException {
    public:
        NotRegisteredException() : IRCException("451", ":You have not registered") {}
        ~NotRegisteredException() throw() {}
};

#endif