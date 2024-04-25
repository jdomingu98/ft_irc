#ifndef TOPIC_RESPONSE_HPP
# define TOPIC_RESPONSE_HPP

# include "AResponse.hpp"

class TopicResponse : public AResponse {
    private:
        std::string _channel;
        std::string _topic;
    public:
        TopicResponse(std::string const &codeNumber, std::string const &nickname, std::string const &channel, std::string const &topic);
        virtual std::string getResponse() const;
};