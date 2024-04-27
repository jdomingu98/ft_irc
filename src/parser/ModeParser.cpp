#include "ModeParser.hpp"

/**
 * Parses the MODE command.
 * 
 * The format of the MODE command is as follows:
 * 
 * Command: MODE
 * 
 * Parameters: <channel> {[+|-]|i|t|k|o|l} [<params>]
 * 
 * @param tokens The tokens to parse.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @throws `UnknownModeException` if the mode is invalid.
 * @return The parsed command.
 *
 */
ACommand *ModeParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException("MODE");
    if (tokens.size() == 2)
        return new ModeCommand(tokens[1]);

    std::string channel = tokens[1];
    std::string modesStr = tokens[2];
    bool plus = modesStr[0] != '-';

    std::vector<Mode> modes;
    for (std::string::const_iterator it = modesStr.begin(); it != modesStr.end(); it++) {
        if (it == modesStr.begin() && (*it == '+' || *it == '-'))
            continue;
        if (*it == 'i')
            modes.push_back(INVITE_ONLY);
        else if (*it == 't')
            modes.push_back(TOPIC_PROTECTED);
        else if (*it == 'k')
            modes.push_back(CHANNEL_KEY);
        else if (*it == 'o')
            modes.push_back(CHANNEL_OPERATOR);
        else if (*it == 'l')
            modes.push_back(USER_LIMIT);
        else
            throw UnknownModeException(std::string(1, *it));
    }

    std::vector<std::string> modeParams;
    for (size_t i = 3; i < tokens.size(); i++) {
        modeParams.push_back(tokens[i]);
    }
    return new ModeCommand(plus, channel, modes, modeParams);
}
