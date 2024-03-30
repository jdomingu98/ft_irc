#include "ModeParser.hpp"

ICommand *ModeParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException("MODE");

    std::string channel = tokens[1];
    std::string modesStr = tokens[2];
    std::string modeParams = tokens.size() > 3 ? tokens[3] : "";
    bool plus = modesStr[0] != '-';

    std::vector<Mode> modes;
    for (size_t i = 0; i < modesStr.size(); i++) {
        if (i == 0 && modesStr[i] == '+' || modesStr[i] == '-')
            continue;
        if (modesStr[i] == 'i')
            modes.push_back(INVITE_ONLY);
        else if (modesStr[i] == 't')
            modes.push_back(TOPIC_PROTECTED);
        else if (modesStr[i] == 'k')
            modes.push_back(CHANNEL_KEY);
        else if (modesStr[i] == 'o')
            modes.push_back(CHANNEL_OPERATOR);
        else if (modesStr[i] == 'l')
            modes.push_back(USER_LIMIT);
        else throw UnknownModeException(modesStr[i]);
    }
    return new ModeCommand(plus, channel, modes, modeParams);
}