#ifndef IZOGAME_CAMERA_H
#define IZOGAME_CAMERA_H

#include <SFML/Graphics.hpp>
#include "DeltaTime.h"
#include "../maps/Map.h"

class Camera {
public:
    void handleEvent(sf::Event &event);

    sf::View &getView();

    static sf::Vector2f getPixelPosition(sf::Vector2i xy);
    static sf::Vector2i getMapPosition(sf::Vector2f xy);

private:
    sf::View view;
};

#endif //IZOGAME_CAMERA_H
