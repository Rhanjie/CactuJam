#ifndef IZOGAME_LOGGER_H
#define IZOGAME_LOGGER_H

#include <iostream>
#include <fstream>
#include "Extensions.h"

class Logger {
public:
    static void info(const std::string& message, bool newLine = true);
    static void debug(const std::string& message, bool newLine = true);
    static void warning(const std::string& message, bool newLine = true);
    static void error(const std::string& message, bool newLine = true);

    static void setDebugMode(bool debugMode);

    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;

    static Logger& getInstance();

private:
    Logger() {
        this->openFile();

        this->saveMessageToFile("* " + getCurrentDate("%F %T") + " *\n");
    }
    ~Logger() {
        file << "\n\n\n";

        file.close();
    }

    void displayMessage(const std::string& prefix, std::string message, bool goToNewLine);
    void saveMessageToFile(const std::string& message);
    bool openFile();

    bool debugMode = false;
    bool enableSavingToFile = false;
    bool isNewLine = true;
    std::fstream file;

    static const std::string INFO_PREFIX;
    static const std::string DEBUG_PREFIX;
    static const std::string WARNING_PREFIX;
    static const std::string ERROR_PREFIX;
};

//bool Logger::debugMode = false;

#endif //IZOGAME_LOGGER_H
