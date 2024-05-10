#ifndef RESPONSE_BUILDER_HPP
# define RESPONSE_BUILDER_HPP

# include <string>

/**
 * This class is responsible for building responses to the IRC server.
 */
class ResponseBuilder {
	private:
		ResponseBuilder();

	public:
		static std::string join(const std::string &channel);
		static std::string part(const std::string &channel);
		static std::string privmsg(const std::string &destination, const std::string &message);
		static std::string user(const std::string &username, const std::string &hostname, const std::string &serverName, const std::string &realName);
		static std::string nick(const std::string &nick);
		static std::string pass(const std::string &password);

		~ResponseBuilder();
};

#endif