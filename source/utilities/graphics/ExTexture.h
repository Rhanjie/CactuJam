#ifndef IZOGAME_EXTEXTURE_H
#define IZOGAME_EXTEXTURE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Logger.h"

class ExTexture: public sf::Texture {
public:
    void init();
    void createMultiTexture(std::string type,
                            unsigned int rows, unsigned int columns,
                            unsigned int wFrame, unsigned int hFrame);

    std::string getType() const {return type;}
    unsigned int getRows() const {return rows;}
    unsigned int getColumns() const {return columns;}
    unsigned int getWFrame() const {return wFrame;}
    unsigned int getHFrame() const {return hFrame;}

private:
    //TODO: Add enum class
    std::string type = "single";

    unsigned int rows    = 1;
    unsigned int columns = 1;
    unsigned int wFrame  = 0;
    unsigned int hFrame  = 0;
};

#endif //IZOGAME_EXTEXTURE_H
