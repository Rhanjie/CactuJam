#ifndef IZOGAME_MANYSPRITES_H
#define IZOGAME_MANYSPRITES_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Logger.h"
#include "ExTexture.h"

class ManySprites {
public:
    explicit ManySprites(const ExTexture &texture);

    std::vector<std::vector<sf::Sprite>> sprites;

    sf::Sprite &getRandomSprite();
    sf::Sprite &getSprite(int x, int y);
};

#endif //IZOGAME_MANYSPRITES_H
