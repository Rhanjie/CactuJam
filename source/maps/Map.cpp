//
// Created by rhanjie on 22.12.18.
//

#include "Map.h"

Map::Map(sf::Vector2u size) {
    this->size = size;
    this->generate();
}

void Map::generate() {
    std::string id = "snow";
    sf::Vector2f pos = sf::Vector2f(0, 0);
    MapTile::Type type = MapTile::NORMAL;

    tiles.push_back(new MapTile("air", MapTile::NORMAL, ResourceManager::getTexture(id), pos));
    tiles.back()->getSprite().setColor(sf::Color::Transparent);

    int height = size.y / 2;

    for (int x = 0; x < size.x; x++) {
        id = "snow";
        type = MapTile::OBSTACLE;

        int random = rand()%100;
        if (random < 40 && height < size.y - 1)
            height += 1;
        else if (random < 80 && random >= 40 && pos.y > 0)
            height -= 1;

        pos.x = x * TILE_WIDTH;
        pos.y = height * TILE_HEIGHT;

        tiles.push_back(new MapTile("snow", MapTile::OBSTACLE, ResourceManager::getTexture(id), pos));
        background.push_back(new MapTile(id, MapTile::NORMAL, ResourceManager::getTexture(id), pos));
        background.back()->getSprite().setColor(sf::Color(100, 100, 100));

        //AIR - nothing
        for (int y = height - 1; y >= 0; y--) {
            //if (x != 0 && y != 0) {
                id = "air";
                pos.x = x * TILE_WIDTH;
                pos.y = y * TILE_HEIGHT;

                tiles.push_back(new MapTile(id, MapTile::NORMAL, ResourceManager::getTexture(id), pos));
                background.push_back(new MapTile(id, MapTile::NORMAL, ResourceManager::getTexture(id), pos));
                background.back()->getSprite().setColor(sf::Color(100, 100, 100));
            //}
        }

        //GROUND
        for (int y = height + 1; y < size.y; y++) {
            id = "dirt";
            pos.x = x * TILE_WIDTH;
            pos.y = y * TILE_HEIGHT;

            if (y > height + 5)
                id = "stone";

            tiles.push_back(new MapTile(id, MapTile::OBSTACLE, ResourceManager::getTexture(id), pos));
            background.push_back(new MapTile(id, MapTile::NORMAL, ResourceManager::getTexture(id), pos));
            background.back()->getSprite().setColor(sf::Color(100, 100, 100));
        }
    }


    //TODO: Caves
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            MapTile* tile = this->getTileOnMapPos(sf::Vector2i(x, y));

            pos.x = x * TILE_WIDTH;
            pos.y = y * TILE_HEIGHT;

            if (tile != tiles.front()) {
                if (tile->getId() == "snow") {
                    id = "air";

                    int startCave = rand()%100;

                    if(startCave > 80) {
                        int index = this->getTileIndexOnMapPos(sf::Vector2i(x, y));

                        this->changeTileByIndex(index, "air", MapTile::NORMAL);
                    }
                }
            }
        }
    }
}

void Map::update(sf::Vector2f mousePosition, sf::View &view) {
    for (auto sprite : tiles) {
        sprite->update();
    }
}

void Map::render(sf::RenderWindow &window) {
    for (auto tile : background) {
        //if (isObjectVisible(tile->getPosition()))
        window.draw(*tile);
    }

    for (auto tile : tiles) {
        //if (isObjectVisible(tile->getPosition()))
        window.draw(*tile);
    }

}

MapTile *Map::getTileOnMapPos(sf::Vector2i position) {
    for (auto &tile : tiles) {
        if (tile->getPosition() == Camera::getPixelPosition(position))
            return tile;
    }

    return tiles.front();
}

MapTile *Map::getTileOnPixelPos(sf::Vector2f position) {
    for (auto tile : tiles) {
        if (tile->getSprite().getGlobalBounds().contains(position))
            return tile;
    }

    return tiles.front();
}

int Map::getTileIndexOnMapPos(sf::Vector2i position) {
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i]->getPosition() == Camera::getPixelPosition(position))
            return i;
    }

    return 0;
}

int Map::getTileIndexOnPixelPos(sf::Vector2f position) {
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i]->getSprite().getGlobalBounds().contains(position))
            return i;
    }

    return 0;
}

void Map::changeTileByIndex(int index, const std::string& id, MapTile::Type type) {
    if (index >= 0 && index < tiles.size())
        (*(tiles.begin() + index)) = new MapTile(id, type, ResourceManager::getTexture(id), (*(tiles.begin() + index))->getPosition());
}
