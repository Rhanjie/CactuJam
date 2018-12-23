#include "Camera.h"
#include <cmath>

void Camera::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::MouseWheelMoved) {
        if (event.mouseWheel.delta == 1)
            view.zoom(0.9);
        if (event.mouseWheel.delta == -1)
            view.zoom(1.1);
    }
}

sf::View &Camera::getView() {
    return view;
}

sf::Vector2f Camera::getPixelPosition(sf::Vector2i mapPosition) {
    return sf::Vector2f(
            float(ceil(mapPosition.x * Map::TILE_WIDTH)),
            float(ceil(mapPosition.y * Map::TILE_HEIGHT))
    );
}

sf::Vector2i Camera::getMapPosition(sf::Vector2f isoPosition) {
    return sf::Vector2i(
            (int)((isoPosition.x + 1) / Map::TILE_WIDTH),
            (int)((isoPosition.y + 1) / Map::TILE_HEIGHT)
    );
}