#ifndef KICK_PARSER_HPP
# define KICK_PARSER_HPP

# include "IParser.hpp"
# include "KickCommand.hpp"

/**
 * An IParser implementation that is responsible for parsing the KICK command.
 */
class KickParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif