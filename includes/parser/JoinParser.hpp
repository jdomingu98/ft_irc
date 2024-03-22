#ifndef JOIN_PARSER_HPP
# define JOIN_PARSER_HPP

# include "IParser.hpp"

# include "JoinCommand.hpp"

# include "libsUtils.hpp"

/**
 * An IParser implementation that is responsible for parsing the JOIN command.
 */
class JoinParser : public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif