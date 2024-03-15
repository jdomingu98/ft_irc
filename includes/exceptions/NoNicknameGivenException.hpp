#ifndef NO_NICKNAME_GIVEN_EXCEPTION_HPP
# define NO_NICKNAME_GIVEN_EXCEPTION_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a nickname is not given in a command that requires one.
 */
class NoNicknameGivenException : public IRCException {
    public:
        NoNicknameGivenException() : IRCException("431", ":No nickname given") {}
        ~NoNicknameGivenException() throw() {}
};

#endif
