#ifndef I_PARSER_HPP
# define I_PARSER_HPP

# include "ICommand.hpp"

# include "libsUtils.hpp"

class ICommand;

/**
 * An interface that represents a parser that is responsible for parsing commands.
 */
class IParser {
    public:
        virtual ICommand *parse(const std::vector<std::string>& tokens) = 0;
        virtual ~IParser() {}
};

#endif