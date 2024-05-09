#ifndef I_PARSER_HPP
# define I_PARSER_HPP

# include <vector>

# include "ACommand.hpp"

# define DOWN "DOWN"
# define INVITE "INVITE"
# define JOIN "JOIN"
# define KICK "KICK"
# define MODE "MODE"
# define NICK "NICK"
# define NOTICE "NOTICE"
# define PART "PART"
# define PASS "PASS"
# define PRIVMSG "PRIVMSG"
# define QUIT "QUIT"
# define TOPIC "TOPIC"
# define UP "UP"
# define USER "USER"
# define WHO "WHO"

class ACommand;

/**
 * An interface that represents a parser that is responsible for parsing commands.
 */
class IParser {
    public:
        virtual ACommand *parse(const std::vector<std::string>& tokens) = 0;
        virtual ~IParser() {}
};

#endif