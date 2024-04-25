#include "libsUtils.hpp"

/**
 * Splits the string by the delimiter.
 * 
 * @param s The string to be split.
 * @param delim The delimiter.
 * 
 * @return The vector of strings.
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
        if (!item.empty())
            elems.push_back(item);
    return elems;
}

/**
 * Checks if the string is a number.
 * 
 * @param s The string to be checked.
 * 
 * @return `true` if the string is a number, `false` otherwise.
 */
bool isNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

/**
 * Gets the current date.
 * 
 * @return The string with the current date.
 */
std::string getCurrentDate() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::ostringstream oss;
    const char* weekDays[7] = {"Sunday", "Monday", "Tuesday",
                                "Wednesday", "Thursday", "Friday", "Saturday"};   
    const char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                                "Aug", "Sep", "Oct", "Nov", "Dec"};

    oss << weekDays[now->tm_wday] << ", " 
        << std::setfill('0') << std::setw(2) << now->tm_mday << ' ' 
        << months[now->tm_mon] << ' ' 
        << (now->tm_year + 1900) << ' '
        << std::setfill('0') << std::setw(2) << now->tm_hour << ':' 
        << std::setfill('0') << std::setw(2) << now->tm_min << ':' 
        << std::setfill('0') << std::setw(2) << now->tm_sec << " UTC";
    return oss.str();
}