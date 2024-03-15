#ifndef NicknameInUseException_HPP
# define NicknameInUseException_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a nickname is already in use.
 * It is thrown when a client tries to change their nickname to one that is already in use.
 */
class NicknameInUseException : public IRCException {
    public:
        NicknameInUseException(const std::string nickname) : IRCException("433", nickname + " :Nickname is already in use") {}
        ~NicknameInUseException() throw() {}
};

#endif