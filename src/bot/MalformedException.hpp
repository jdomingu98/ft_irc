#ifndef MALFORMED_EXCEPTION_HPP
# define MALFORMED_EXCEPTION_HPP

# include <exception>

# define MALFORMED_EXCEPTION_MESSAGE(message) "Malformed message: " + (message)

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