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
    if (tokens.size() <3)
        throw NeedMoreParamsException("MODE");

    std::string channel = tokens[1];
    std::string modesStr = tokens[2];
    bool plus = modesStr[0] != '-';

    std::vector<Mode> &modes = parseModes(modesStr);

    std::vector<std::string> modeParams;
    for (size_t i = 3; i < tokens.size(); i++) {
        modeParams.push_back(tokens[i]);
    }
    return new ModeCommand(plus, channel, modes, modeParams);
}

/**
 * Parses the modes of the MODE command.
 */
std::vector<Mode> &ModeParser::parseModes(const std::string& modesStr) {
    std::vector<Mode> modes;
    for (std::string::const_iterator it = modesStr.begin(); it != modesStr.end(); it++) {
        if (it == modesStr.begin() && (*it == '+' || *it == '-'))
            continue;
        if (!ModeParser::isValidMode(*it))
            throw UnknownModeException(std::string(1, *it));
        modes.push_back(static_cast<Mode>(*it));
    }
    return modes;
}

/**
 * Checks if the mode is valid.
 */
bool ModeParser::isValidMode(char mode) {
    return mode == INVITE_ONLY || mode == TOPIC_PROTECTED || mode == CHANNEL_KEY || mode == CHANNEL_OPERATOR || mode == USER_LIMIT;
}