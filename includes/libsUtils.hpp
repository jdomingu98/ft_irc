#ifndef LIBS_UTILS_HPP
# define LIBS_UTILS_HPP

/**
 * A file that contains utility consts and libraries that are used along the project.
*/

# include <sstream>
# include <vector>

// ========================================= IRC SERVER ERROR MESSAGES =========================================

std::vector<std::string> split(const std::string &s, char delim);

bool isNumber(const std::string& s);
std::string getCurrentDate();

#endif