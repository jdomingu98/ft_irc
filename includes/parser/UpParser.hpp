#ifndef UP_PARSER_HPP
# define UP_PARSER_HPP

# include "UpCommand.hpp"
# include "IParser.hpp"

/**
 * An IParser implementation that is responsible for parsing the UP command.
 */
class UpParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif