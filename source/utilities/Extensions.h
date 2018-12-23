#ifndef IZOGAME_EXTENSIONS_H
#define IZOGAME_EXTENSIONS_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>

std::string getCurrentDate(const std::string& format);
std::vector<std::string> split(char delim, std::string const &text);
int randInt(int min, int max);
int randInt(int max);

#endif //IZOGAME_EXTENSIONS_H
