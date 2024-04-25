#include "TopicResponse.hpp"

/**
 * Constructs a new TopicResponse.
 * 
 * @param codeNumber The code number of the response
 * @param nickname The nickname of the user
 * @param channel The channel of the topic
 * @param topic The topic of the channel
 */
TopicResponse::TopicResponse(std::string const &codeNumber, std::string const &nickname, std::string const &channel, std::string const &topic)
    : AResponse(codeNumber, nickname), _channel(channel), _topic(topic) {}

/**
 * Gets the response.
 * 
 * @return The response
 */
std::string TopicResponse::getResponse() const {
    return RESPONSE_MSG(_codeNumber, _nickname, RPL_TOPIC(_channel, _topic));
}