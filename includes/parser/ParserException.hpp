#ifndef PARSER_EXCEPTION_HPP
# define PARSER_EXCEPTION_HPP

# include <string>

class ParserException: public std::exception {
    private:
        std::string _message;
    public:
        ParserException(const std::string& msg) : _message(msg) {}
        ~ParserException() throw() {}

        virtual const char* what() const throw() {
            return _message.c_str();
        }
};

#endif
