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
    const SenderEntity *sender = message.getSender();
    if (sender->isServer()) {
        // De momento no handleamos los mensajes del servidor. Gracias por su visita. Por favor, cierra la puerta al salir.
    } else {
        if (message.getCommand() == "PRIVMSG")
            this->onPrivateMessage(message);
        else if (message.getCommand() == "JOIN")
            this->onJoin(message);
    }
}

void GlaskBot::onPrivateMessage(const Message &message) {
    const SenderEntity *sender = message.getSender();
    std::string destination = sender->getNickname();
    const std::string &params = message.getParams();
    std::vector<std::string> messageParts = GlaskBot::split(params);
    if (messageParts.size() < 2)
        return ;
    std::string receiver(messageParts[0]);
    if (receiver == BOT_NAME) {
        if (messageParts[1] == ":!join")
            joinChannel(destination, messageParts);
    } else if (isChannel(receiver)) {
        if (messageParts[1] == ":!message")
            setMessage(messageParts);
    }
}

void GlaskBot::onJoin(const Message &message)
{
    const SenderEntity *sender = message.getSender();
    std::string channel = message.getParams();
    std::string welcomeUser = sender->getNickname();
    std::string nickname = sender->getNickname();
    if (nickname == BOT_NAME) {
        this->sendData(ResponseBuilder::privmsg(channel, "ME HE UNIDO A TU CANAL"));
    } else {
        std::string welcomeMessage = welcomeMessages[channel];
        if (!welcomeMessage.empty()) {
            if (welcomeMessage.find("{}") != std::string::npos)
                welcomeMessage = welcomeMessage.replace(welcomeMessage.find("{}"), 2, welcomeUser);
            this->sendData(ResponseBuilder::privmsg(channel, welcomeMessage));
        }
    }
}

void GlaskBot::joinChannel(const std::string &destination, const std::vector<std::string> &messageParts) {
    std::string channel(messageParts[2]);
    if (messageParts.size() != 3) {
        this->sendData(ResponseBuilder::privmsg(destination, "usage: !join <channel>"));
        return ;
    }
    if (!isChannel(channel)) {
        channel = "#" + channel;
    }
    this->sendData(ResponseBuilder::privmsg(destination, "Joining channel " + channel));
    this->sendData(ResponseBuilder::join(channel));
}

void GlaskBot::setMessage(const std::vector<std::string> &messageParts) {
    std::string channel = messageParts[0];
    if (messageParts[2] == "set") {
        if (messageParts.size() < 4) {
            this->sendData(ResponseBuilder::privmsg(channel, "usage: !message set <message>"));
            return ;
        }
        std::string welcomeMessage;
        for (size_t i = 3; i < messageParts.size(); ++i) {
            welcomeMessage += messageParts[i];
            if (i != messageParts.size() - 1) 
                welcomeMessage += " ";
        }
        welcomeMessages[channel] = welcomeMessage;
        this->sendData(ResponseBuilder::privmsg(channel, "Set welcome message for channel " + channel));
    } else if (messageParts[2] == "unset") {
        if (messageParts.size() != 3) {
            this->sendData(ResponseBuilder::privmsg(channel, "usage: !message unset"));
            return ;
        }
        welcomeMessages.erase(channel);
        this->sendData(ResponseBuilder::privmsg(channel, "Unset welcome message for channel " + channel));
    } else {
        this->sendData(ResponseBuilder::privmsg(channel, "usage: !message <set|unset> <message>"));
    }

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