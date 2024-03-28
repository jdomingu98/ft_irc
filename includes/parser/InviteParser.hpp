#ifndef INVITE_PARSER_HPP
# define INVITE_PARSER_HPP

# include "libsUtils.hpp"
# include "IParser.hpp"
# include "InviteCommand.hpp"

/**
 * An IParser implementation that is responsible for parsing the INVITE command.
 */
class InviteParser : public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif