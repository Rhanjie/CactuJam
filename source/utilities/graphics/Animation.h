#ifndef IZOGAME_ANIMATION_H
#define IZOGAME_ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "../Logger.h"
#include "ExTexture.h"

struct AnimationData {
    int row = 1;
    int col = 1;

    sf::Time frameTime = sf::seconds(1);
};

class Animation {
public:
    Animation(const ExTexture &_texture);

    const ExTexture &texture;
    std::vector<sf::Sprite*>sprites;

    std::map<std::string, AnimationData> data;

    void play();

    void set(const std::string& id);
    void add(const std::string& id, int row, int columns, sf::Time frameTime);
    void addSprite(sf::Sprite* sprite);

    void loadAnimationsFromLua(const std::string& id);

    std::string getCurrAnimName();

private:
    sf::Time frameTime;
    sf::Clock frameClock;

    std::string currAnimName = "";
    int currentAnim = 0;
    int currentFrame = 0;

    void setNextFrame();
};

#endif //IZOGAME_ANIMATION_H
