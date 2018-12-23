#include "MapTile.h"
#include "../Map.h"

MapTile::MapTile(const std::string &id, Type type, const ExTexture &texture, sf::Vector2f position)
        : MapRenderedObject(id, texture, position) {
    this->loadLuaValues(texture);

    this->type = type;
}

void MapTile::update() {
    MapRenderedObject::update();
}

bool MapTile::getBuildBlock() {
    return buildBlock;
}

void MapTile::loadLuaValues(const ExTexture &texture) {
    //MapRenderedObject::loadLuaValues(texture);

    if (ResourceManager::getRawAttribute(id, "buildBlock") != sol::nil)
        buildBlock = (ResourceManager::getRawAttribute(id, "buildBlock").as<std::string>() == "true");
}

MapTile::Type MapTile::getType() const {
    return type;
}

void MapTile::setType(MapTile::Type type) {
    MapTile::type = type;
}
