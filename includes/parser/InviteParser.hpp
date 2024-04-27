#ifndef INVITE_PARSER_HPP
# define INVITE_PARSER_HPP

# include "InviteCommand.hpp"
# include "IParser.hpp"

/**
 * An IParser implementation that is responsible for parsing the INVITE command.
 */
class InviteParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif