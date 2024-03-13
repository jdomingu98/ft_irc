#ifndef QUITPARSER_HPP
# define QUITPARSER_HPP

#include "libsUtils.hpp"
#include "IParser.hpp"
#include "QuitCommand.hpp"
#include "exceptions/ParserException.hpp"


class QuitParser : public Parser
{
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif