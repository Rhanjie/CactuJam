#include "MapRenderedObject.h"

MapRenderedObject::MapRenderedObject(const std::string &id, const ExTexture &texture, sf::Vector2f position)
    : id(id) {
    if(texture.getType() == "multi")
        sprite = ResourceManager::getMultiSprite(id).getRandomSprite();

    else sprite.setTexture(texture);

    sprite.setPosition(position);
    this->loadLuaValues(texture);
}

sf::Sprite &MapRenderedObject::getSprite() {
    return sprite;
}

/*void MapRenderedObject::setSprite(const sf::Texture &texture) {
    //sprite.setTexture(texture);
    //sprite = ResourceManager::getMultiSprite(id).getRandomSprite();
}*/

std::string MapRenderedObject::getId() const {
    return id;
}

void MapRenderedObject::setId(const std::string &id) {
    this->id = id;
}

sf::Vector2f MapRenderedObject::getPosition() const{
    return sprite.getPosition();
}

void MapRenderedObject::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void MapRenderedObject::setDefaultColor() {
    normalColor = sprite.getColor();
}

void MapRenderedObject::resetColor() {
    sprite.setColor(normalColor);
}

void MapRenderedObject::loadLuaValues(const ExTexture &texture) {
    if (ResourceManager::getRawAttribute(id, "positionDiffY") != sol::nil)
        sprite.move(0, ResourceManager::getRawAttribute(id, "positionDiffY").as<int>());

    if (ResourceManager::getRawAttribute(id, "positionDiffX") != sol::nil)
        sprite.move(ResourceManager::getRawAttribute(id, "positionDiffX").as<int>(), 0);
}

void MapRenderedObject::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite);
}

sf::Vector2i MapRenderedObject::getSize() const {
    return sf::Vector2i(
            (int)sprite.getGlobalBounds().width  / 2,
            (int)sprite.getGlobalBounds().height / 2);
}

//TODO: Optimize sort method
bool MapRenderedObject::isHigherThanFirst(MapRenderedObject *first, MapRenderedObject *second) {
    float firstY = first->getPosition().y + first->getSize().y * 2;
    float secondY = second->getPosition().y + second->getSize().y * 2;

    return ((firstY  < secondY) || (firstY == secondY &&
    (first->getSize().x < second->getSize().x || first->getSize().y < second->getSize().y)));
}
