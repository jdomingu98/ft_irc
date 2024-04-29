#ifndef WHO_PARSER_HPP
# define WHO_PARSER_HPP

# include "IParser.hpp"
# include "WhoCommand.hpp"

/**
 * An IParser implementation that is responsible for parsing the WHO command.
 */
class WhoParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif