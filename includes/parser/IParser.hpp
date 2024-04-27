#ifndef I_PARSER_HPP
# define I_PARSER_HPP

# include "ACommand.hpp"

# include "Utils.hpp"

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