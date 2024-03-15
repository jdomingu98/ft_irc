#ifndef ERRONEOUS_NICKNAME_EXCEPTION_HPP
# define ERRONEOUS_NICKNAME_EXCEPTION_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a nickname is erroneous. (Invalid characters, so long, etc.)
 */
class ErroneousNicknameException : public IRCException {
    public:
        ErroneousNicknameException(const std::string nickname) : IRCException("432", nickname + " :Erroneous nickname") {}
        ~ErroneousNicknameException() throw() {}
};

#endif