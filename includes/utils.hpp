#ifndef UTILS_HPP
# define UTILS_HPP

/**
 * A utility file that contains various utility functions.
 */

# include <string>
# include <vector>
# include <sstream>

std::string trim(const std::string& str);
std::vector<std::string> split(const std::string &s, char delim);

#endif