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

    std::map<char, Mode> modeChar;
    modeChar['i'] = INVITE_ONLY;
    modeChar['t'] = TOPIC_PROTECTED;
    modeChar['k'] = CHANNEL_KEY;
    modeChar['o'] = CHANNEL_OPERATOR;
    modeChar['l'] = USER_LIMIT;

    std::vector<Mode> modes;
    const std::string &modesTok = tokens[2];
    std::string::const_iterator it;
    for (it = modesTok.begin(); it != modesTok.end(); it++) {
        if (it == modesTok.begin() && (*it == '+' || *it == '-'))
            continue;
        if (modeChar.find(*it) != modeChar.end())
            modes.push_back(modeChar.at(*it));
        else
            throw UnknownModeException(std::string(1, *it));
    }

    std::vector<std::string> modeParams;
    for (size_t i = 3; i < tokens.size(); i++)
        modeParams.push_back(tokens[i]);

    return new ModeCommand(modesTok[0] != '-', tokens[1], modes, modeParams);
}
