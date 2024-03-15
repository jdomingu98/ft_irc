#ifndef ALREADY_REGISTERED_EXCEPTION_HPP
# define ALREADY_REGISTERED_EXCEPTION_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a user attempts to register with the server when it is already registered.
*/
class AlreadyRegisteredException : public IRCException {
    public:
        AlreadyRegisteredException() : IRCException("462", ":You may not reregister") {}
        ~AlreadyRegisteredException() throw() {}
};

#endif
