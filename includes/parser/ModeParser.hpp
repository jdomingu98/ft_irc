#ifndef MODE_PARSER_HPP
# define MODE_PARSER_HPP

# include "IParser.hpp"
# include "ModeCommand.hpp"

class ModeParser : public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif