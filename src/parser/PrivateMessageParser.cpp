#include "PrivateMessageParser.hpp"

/**
 * Parses the PRIVMSG command.
 * 
 * The format of the PRIVMSG command is as follows:
 * 
 * Command: PRIVMSG
 * Parameters: <receiver>{,<receiver>} <text to be sent>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NoRecipientGivenException` if no recipient is given.
 * @throws `NoTextToSendException` if no text is given.
 * @return The parsed command.
 */
ICommand* PrivateMessageParser::parse(const std::vector<std::string>& tokens) {
    std::vector<std::string> receivers;
    std::string message;

    size_t i = 1;
    while (i < tokens.size() && tokens[i][0] != ':') {
        receivers.push_back(tokens[i]);
        i++;
    }
    if (i == 1) {
        throw NoRecipientGivenException("PRIVMSG");
    }
    if (i == tokens.size()) {
        throw NoTextToSendException();
    }
    message = tokens[i].substr(1);
    for (size_t j = i + 1; j < tokens.size(); j++) {
        message += " " + tokens[j];
    }

    return new PrivateMessageCommand(receivers, message);
}
