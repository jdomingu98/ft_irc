#ifndef DOWN_PARSER_HPP
# define DOWN_PARSER_HPP

# include "DownCommand.hpp"
# include "IParser.hpp"

/**
 * An IParser implementation that is responsible for parsing the DOWN command.
 */
class DownParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif