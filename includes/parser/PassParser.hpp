#ifndef PASS_PARSER_HPP
# define PASS_PARSER_HPP

# include "IParser.hpp"

# include "PassCommand.hpp"

# include "Utils.hpp"

/**
 * An IParser implementation that is responsible for parsing the PASS command.
 */
class PassParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif