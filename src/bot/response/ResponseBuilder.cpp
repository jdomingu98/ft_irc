#include "ResponseBuilder.hpp"

ResponseBuilder::ResponseBuilder() {}

ResponseBuilder::~ResponseBuilder() {}

std::string ResponseBuilder::join(const std::string &channel) {
	return "JOIN " + channel;
}

std::string ResponseBuilder::part(const std::string &channel) {
	return "PART " + channel;
}

std::string ResponseBuilder::privmsg(const std::string &destination, const std::string &message) {
	return "PRIVMSG " + destination + " :" + message;
}

std::string ResponseBuilder::user(
	const std::string &username,
	const std::string &hostname,
	const std::string &serverName,
	const std::string &realName) {
	return "USER " + username + " " + hostname + " " + serverName + " :" + realName;
}

std::string ResponseBuilder::nick(const std::string &nick) {
	return "NICK " + nick;
}

std::string ResponseBuilder::pass(const std::string &pass) {
	return "PASS " + pass;
}