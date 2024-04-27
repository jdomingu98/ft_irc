#ifndef QUIT_PARSER_HPP
# define QUIT_PARSER_HPP

# include "IParser.hpp"
# include "QuitCommand.hpp"

/**
 * A class that is responsible for parsing the QUIT command.
 * 
 */
class QuitParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif