#ifndef NICK_COLLISION_EXCEPTION_HPP
# define NICK_COLLISION_EXCEPTION_HPP

# include "IRCException.hpp"

/**
 * This exception is thrown when a nickname is already in use. (Nickname collision)
 * It is thrown when a user tries to set a nickname the first time, and it is already in use.
 */
class NickCollisionException : public IRCException {
    public:
        NickCollisionException(const std::string nickname) : IRCException("436", nickname + " :Nickname collision KILL") {}
        ~NickCollisionException() throw() {}
};

#endif