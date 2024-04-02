#ifndef KICK_PARSER_HPP
# define KICK_PARSER_HPP

# include "IParser.hpp"

# include "KickCommand.hpp"

# include "libsUtils.hpp"

/**
 * An IParser implementation that is responsible for parsing the KICK command.
 */
class KickParser : public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif