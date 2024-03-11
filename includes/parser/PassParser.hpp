#ifndef PASS_PARSER_HPP
# define PASS_PARSER_HPP

# include "libsUtils.hpp"
# include "PassCommand.hpp"
# include "IParser.hpp"
# include "exceptions/ParserException.hpp"

class PassParser: public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);

};

#endif