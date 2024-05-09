#include "GlaskBot.hpp"

/**
 * GlaskBot constructor
 * 
 * @param address The address of the server
 * @param port The port of the server
 */
GlaskBot::GlaskBot(const std::string &address, int port, const std::string &password) : IRCClient(address, port) {
	if (!password.empty())
		this->sendData(ResponseBuilder::pass(password));
    this->sendData(ResponseBuilder::nick(BOT_NAME));
    this->sendData(ResponseBuilder::user(BOT_NAME, "*", "*", BOT_NAME + std::string("Bot")));
    this->startLoop();
}

/**
 * GlaskBot destructor
 */
GlaskBot::~GlaskBot() {}

/**
 * This function aims to handle the response from the server.
 * 
 * @param response The response from the server.
 */
void GlaskBot::handleResponse(const Message &message) {
    try {
        if (message.getSender()->isServer()) {
            // De momento no handleamos los mensajes del servidor. Gracias por su visita. Por favor, cierra la puerta al salir.
        } else {
            if (message.getCommand() == "PRIVMSG")
                this->onPrivateMessage(message);
            else if (message.getCommand() == "JOIN")
                this->onJoin(message);
        }
    } catch (const BadUsageException &e) {
        this->sendData(ResponseBuilder::privmsg(e.getTo(), e.what()));
    }
}

void GlaskBot::onPrivateMessage(const Message &message) {
    std::string destination = message.getSender()->getNickname();
    std::vector<std::string> messageParts = GlaskBot::split(message.getParams());

    if (messageParts.size() < 2)
        return ;

    std::string receiver(messageParts[0]);
    if (receiver == BOT_NAME) {
        if (messageParts[1] == ":!join")
            joinChannel(destination, messageParts);
        // add here more commands to handle on private chat
    } else if (isChannel(receiver)) {
        if (messageParts[1] == ":!message")
            setMessage(messageParts);
        // add here more commands to handle on channels
    }
}

void GlaskBot::onJoin(const Message &message) {
    const SenderEntity *sender = message.getSender();
    std::string channel = message.getParams();
    std::string nickname = sender->getNickname();

    
    if (nickname == BOT_NAME) // Bot is joining the channel (Tell the channel he is joining)
        this->sendData(ResponseBuilder::privmsg(channel, BOT_JOINNING_MESSAGE));
    else { // An user is joining the channel (send welcome message if set)
        std::string welcomeMessage = welcomeMessages[channel];
        if (!welcomeMessage.empty()) {
            if (welcomeMessage.find("{}") != std::string::npos)
                welcomeMessage = welcomeMessage.replace(welcomeMessage.find("{}"), 2, nickname);
            this->sendData(ResponseBuilder::privmsg(channel, welcomeMessage));
        }
    }
}

void GlaskBot::joinChannel(const std::string &destination, const std::vector<std::string> &messageParts) {
    std::string channel(messageParts[2]);
    if (messageParts.size() != 3)
        throw BadUsageException(destination, "!join <channel>");
    if (!isChannel(channel))
        channel = "#" + channel;
    this->sendData(ResponseBuilder::privmsg(destination, "Joining channel " + channel));
    this->sendData(ResponseBuilder::join(channel));
}

void GlaskBot::setMessage(const std::vector<std::string> &messageParts) {
    std::string channel = messageParts[0];
    if (messageParts.size() < 3)
        throw BadUsageException(channel, "!message <set|unset> <message>");
    if (messageParts[2] == "set") {
        if (messageParts.size() < 4)
            throw BadUsageException(channel, "!message set <message>");
        std::string welcomeMessage;
        for (size_t i = 3; i < messageParts.size(); ++i) {
            welcomeMessage += messageParts[i];
            if (i != messageParts.size() - 1) 
                welcomeMessage += " ";
        }
        welcomeMessages[channel] = welcomeMessage;
        this->sendData(ResponseBuilder::privmsg(channel, "Set welcome message for channel " + channel));
    } else if (messageParts[2] == "unset") {
        if (messageParts.size() != 3)
            throw BadUsageException(channel, "!message unset");
        welcomeMessages.erase(channel);
        this->sendData(ResponseBuilder::privmsg(channel, "Unset welcome message for channel " + channel));
    } else throw BadUsageException(channel, "!message <set|unset> <message>");

}

std::vector<std::string> GlaskBot::split(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, ' '))
        if (!item.empty())
            elems.push_back(item);
    return elems;
}

bool GlaskBot::isChannel(const std::string &receiver) {
    return receiver.length() > 0 && (receiver[0] == '#' || receiver[0] == '&');
}