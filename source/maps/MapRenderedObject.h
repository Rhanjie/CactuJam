#ifndef IZOGAME_MAPRENDEREDOBJECT_H
#define IZOGAME_MAPRENDEREDOBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../utilities/graphics/ExTexture.h"
#include "../utilities/graphics/ManySprites.h"
#include "../utilities/graphics/ResourceManager.h"

class MapRenderedObject: public sf::Drawable {
public:
    MapRenderedObject(const std::string &id, const ExTexture &texture, sf::Vector2f position);

    sf::Sprite &getSprite();
    //void setSprite(const sf::Texture &texture);

    std::string getId() const;
    void setId(const std::string &id);

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);

    sf::Vector2i getSize() const;

    virtual void update(){};

    void setDefaultColor();
    void resetColor();

    static bool isHigherThanFirst(MapRenderedObject* first, MapRenderedObject* second);

protected:
    std::string id = "";
    //sf::Vector2f position = sf::Vector2f(0, 0);

    sf::Sprite sprite;
    sf::Color normalColor = sf::Color::White;

    virtual void loadLuaValues(const ExTexture &texture);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //IZOGAME_MAPRENDEREDOBJECT_H
