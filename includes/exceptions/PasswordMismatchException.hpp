#ifndef PASSWORD_MISMATCH_EXCEPTION_HPP
# define PASSWORD_MISMATCH_EXCEPTION_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a password is incorrect.
 */
class PasswordMismatchException : public IRCException {
    public:
        PasswordMismatchException() : IRCException("464", ":Password incorrect") {}
        ~PasswordMismatchException() throw() {}
};

#endif