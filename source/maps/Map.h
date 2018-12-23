#ifndef CACTUJAM_MAP_H
#define CACTUJAM_MAP_H

#include <SFML/Graphics/Texture.hpp>
#include "../utilities/Logger.h"
#include "../utilities/Camera.h"
#include "../utilities/graphics/ResourceManager.h"
#include "tiles/MapTile.h"

class Map {
public:
    static const int TILE_WIDTH = 50, TILE_HEIGHT = 50;

    Map(sf::Vector2u size);
    void generate();

    void update(sf::Vector2f mousePosition, sf::View& view);
    void render(sf::RenderWindow &window);

    //bool isObjectVisible(sf::Vector2f objPos, sf::Vector2i objSize = sf::Vector2i(0, 0));

    MapTile* getTileOnMapPos(sf::Vector2i position);
    MapTile* getTileOnPixelPos(sf::Vector2f position);

    int getTileIndexOnMapPos(sf::Vector2i position);
    int getTileIndexOnPixelPos(sf::Vector2f position);

    void changeTileByIndex(int index, const std::string& id, MapTile::Type type);


private:
    std::vector<MapTile*> tiles;
    std::vector<MapTile*> background;

    sf::Vector2u size = sf::Vector2u(10, 10);
};

#endif //CACTUJAM_MAP_H
