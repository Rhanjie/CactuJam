#include "Logger.h"

const std::string Logger::INFO_PREFIX       = "[INFO]  : ";
const std::string Logger::DEBUG_PREFIX      = "[DEBUG] : ";
const std::string Logger::WARNING_PREFIX    = "[WARN]  : ";
const std::string Logger::ERROR_PREFIX      = "[ERROR] : ";

/**
 * Use method displayMessage with normal prefix
 * @param const std::string& message
 * @param bool newLine
 */
void Logger::info(const std::string& message, bool newLine) {
    Logger::getInstance().displayMessage(Logger::INFO_PREFIX, message, newLine);
}

/**
 * Use method displayMessage with debug prefix
 * @param const std::string& message
 * @param bool newLine
 */
void Logger::debug(const std::string& message, bool newLine) {
    if (Logger::getInstance().debugMode)
        Logger::getInstance().displayMessage(Logger::DEBUG_PREFIX, message, newLine);
}

/**
 * Use method displayMessage with warning prefix
 * @param const std::string& message
 * @param bool newLine
 */
void Logger::warning(const std::string& message, bool newLine) {
    Logger::getInstance().displayMessage(Logger::WARNING_PREFIX, message, newLine);
}

/**
 * Use method displayMessage with error prefix
 * @param const std::string& message
 * @param bool newLine
 */
void Logger::error(const std::string& message, bool newLine) {
    Logger::getInstance().displayMessage(Logger::ERROR_PREFIX, message, newLine);
}


/**
 * Display the message using parameters given by methods above
 * @param const std::string& prefix
 * @param std::string message
 * @param bool goToNewLine
 */
void Logger::displayMessage(const std::string& prefix, std::string message, bool goToNewLine) {
    if (isNewLine)
        message = prefix + message;

    if (goToNewLine) {
        message += "\n";

        isNewLine = true;
    }    else isNewLine = false;

    //TODO: Add colored messages
    //std::cout << rang::style::bold << rang::fg::green << message;
    std::cout << message;

    saveMessageToFile(message);
}

/**
 * Creating/open file for saving logs
 * @return bool
 */
bool Logger::openFile() {
    std::string path = "assets/logs/" + getCurrentDate("%F") + ".log";

    file.open(path, std::ios::app);

    if (file.fail()){
        Logger::warning("Problem with opening \"" + path + "\" file!");
        enableSavingToFile = false;

        return false;
    }

    enableSavingToFile = true;
    return true;
}

/**
 * Create/open file for saving logs
 * @param const std::string& message
 */
void Logger::saveMessageToFile(const std::string& message) {
    if (enableSavingToFile) {
        file.write(&message[0], message.length());
    }
}

/**
 * Set logger debug mode
 * @param bool debugMode
 */
void Logger::setDebugMode(bool debugMode) {
    Logger::getInstance().debugMode = debugMode;
}

/**
 * Get the logger instance
 * @param bool debugMode
 * @return Logger&
 */
Logger& Logger::getInstance() {
    static Logger instance;

    return instance;
}
