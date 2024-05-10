#ifndef MALFORMED_EXCEPTION_HPP
# define MALFORMED_EXCEPTION_HPP

# include <exception>
# include <string>

# define MALFORMED_EXCEPTION_MESSAGE(message) "Malformed message: " + (message)

/**
 * Exception thrown when a message is malformed
 */
class MalformedException : public std::exception {
	private:
		std::string _message;
	public:
		MalformedException(const std::string &message)
			: _message(MALFORMED_EXCEPTION_MESSAGE(message)) {};

		virtual ~MalformedException() throw() {}

		virtual const char *what() const throw() {
			return _message.c_str();
		};
};
#endif