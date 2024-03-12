#ifndef NICKPARSER_HPP
# define NICKPARSER_HPP

# include "IParser.hpp"
# include "libsUtils.hpp"
# include "commands/NickCommand.hpp"
# include "exceptions/ParserException.hpp"

class NickParser: public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif