#include "PrivateMessageParser.hpp"

/**
 * Parses the private message command.
 * 
 * @param server the server
 * @param fd the file descriptor
 * @param message the message to parse with the following format: "PRIVMSG <receiver>[, <receiver>] :<message>"
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
