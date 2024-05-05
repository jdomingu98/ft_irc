#ifndef RESPONSE_BUILDER_HPP
# define RESPONSE_BUILDER_HPP

# include <string>

class ResponseBuilder {
	private:
		ResponseBuilder();
	public:
		static std::string join(const std::string &channel);
		static std::string part(const std::string &channel);
		static std::string privmsg(const std::string &destination, const std::string &message);
		
		~ResponseBuilder();
};

#endif