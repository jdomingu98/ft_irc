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
				if (messageParts[1] == ":!join") {
						this->sendData(ResponseBuilder::privmsg(destination, "Joining channel " + messageParts[2]));
						this->sendData(ResponseBuilder::join(messageParts[2]));
				}
		}
}

void GlaskBot::onJoin(const Message &message)
{
		const SenderEntity *sender = message.getSender();
		std::string channel = message.getParams();
		std::string welcomeUser = sender->getNickname();
		std::string nickname = sender->getNickname();
		if (nickname == BOT_NAME)
				this->sendData(ResponseBuilder::privmsg(channel, "ME HE UNIDO A TU CANAL DE MIERDAAA HIJO DE PUTA DE MIERDAAA. ME CAGO EN TU PUTA MADRE."));
		else
				this->sendData(ResponseBuilder::privmsg(channel, "Welcome to the channel, " + welcomeUser + "!!!" ));
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
