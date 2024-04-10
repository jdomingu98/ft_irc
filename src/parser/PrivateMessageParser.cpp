#include "PrivateMessageParser.hpp"

/**
 * Parses the PRIVMSG command.
 * 
 * The format of the PRIVMSG command is as follows:
 * 
 * Command: PRIVMSG
 * Parameters: <receiver>{,<receiver>} :<text to be sent>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NoRecipientGivenException` if no recipient is given.
 * @throws `NoTextToSendException` if no text is given.
 * @return The parsed command.
 */
ACommand* PrivateMessageParser::parse(const std::vector<std::string>& tokens) {
    std::vector<std::string> receivers;
    std::string message;

    if (tokens.size() < 2 || tokens[1][0] == ':')
        throw NoRecipientGivenException("PRIVMSG");
    receivers = split(tokens[1], ',');
    if (tokens.size() < 3 || tokens[2][0] != ':')
        throw NoTextToSendException();
    message = tokens[2].substr(1);
    for (size_t i = 2; i < tokens.size(); i++)
        message += " " + tokens[i];

    return new PrivateMessageCommand(receivers, message);
}
