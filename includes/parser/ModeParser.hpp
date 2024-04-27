#ifndef MODE_PARSER_HPP
# define MODE_PARSER_HPP

# include "IParser.hpp"
# include "ModeCommand.hpp"

/**
 * An IParser implementation that is responsible for parsing the MODE command.
 */
class ModeParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif