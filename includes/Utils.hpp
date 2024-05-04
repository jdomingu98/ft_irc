#ifndef UTILS_HPP
# define UTILS_HPP

/**
 * A file that contains utility functions that are used along the project.
*/

# include <sstream>
# include <vector>

class Utils {
    private:
        Utils();
        ~Utils();
    public:
        static std::vector<std::string> split(const std::string &s, const char delim);
        static bool isNumber(const std::string& s);
};

#endif