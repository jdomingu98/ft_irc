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
