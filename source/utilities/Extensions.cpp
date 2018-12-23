#include "Extensions.h"

/**
 * Get the current date as a string
 * @param const std::string& format
 * @return std::string
 */
std::string getCurrentDate(const std::string& format) {
    auto currentDate = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentDate);

    std::stringstream stream;
    stream << std::put_time(std::localtime(&currentTime), format.c_str());

    return stream.str();
}

/**
 * Explode (split) string by delimeter (like explode func in PHP ;)
 * @param delim
 * @param text
 * @return std::vector<std::string>
 */
std::vector<std::string> split(char delim, std::string const &text) {
    std::vector<std::string> res;
    std::istringstream iss(text);
    for (std::string token; std::getline(iss, token, delim); ) {
        res.push_back(std::move(token));
    }
    return res;
}

/**
 * Get random number in min-max range (inclusive)
 * @param int min
 * @param int max
 * @return int
 */
int randInt(int min, int max) {
    if (max <= min) return min;
    return rand()%(max - min + 1) + min;
}

/**
 * Get random number from 0 to max (inclusive)
 * @param max
 * @return
 */
int randInt(int max) {
    return randInt(0, max);
}