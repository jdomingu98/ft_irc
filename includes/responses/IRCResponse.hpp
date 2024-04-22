#ifndef IRC_RESPONSE_HPP
# define IRC_RESPONSE_HPP

# include <string>

# include "Server.hpp"

# define CODE_MSG(errorCode, nickname, errorMsg) ":irc.ft_messenger.net " + (errorCode) +  " " + (nickname) + " " + (errorMsg) + "."

class Channel;

/**
 * A class that represents a response to a command.
 */
class IRCResponse {
    private:
        std::string _responseCode;
        std::string _nickname;
        std::string _message;

    public:
        IRCResponse(const std::string &responseCode, const std::string& nickname, const std::string& msg)
            : _responseCode(responseCode), _nickname(nickname), _message(msg) {}
        ~IRCResponse() {}

        virtual std::string getResponse() const {
            return CODE_MSG(_responseCode, _nickname, _message);
        }
};

#endif