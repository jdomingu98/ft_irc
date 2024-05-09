#ifndef BAD_USAGE_EXCEPTION_HPP
# define BAD_USAGE_EXCEPTION_HPP

# include <exception>
# include <string>

# define USAGE_EXCEPTION_MESSAGE(message) "usage: " + (message)

class BadUsageException : public std::exception {
	private:
		std::string _message;
		std::string _to;
	public:
		BadUsageException(const std::string &to, const std::string &message)
			: _message(USAGE_EXCEPTION_MESSAGE(message)), _to(to) {};

		virtual ~BadUsageException() throw() {}

		virtual const char *what() const throw() {
			return _message.c_str();
		};

		const std::string &getTo() const {
			return _to;
		}
};
#endif