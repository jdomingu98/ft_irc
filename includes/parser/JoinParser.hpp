#ifndef JOIN_PARSER_HPP
# define JOIN_PARSER_HPP

# include "IParser.hpp"
# include "JoinCommand.hpp"

/**
 * An IParser implementation that is responsible for parsing the JOIN command.
 */
class JoinParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif