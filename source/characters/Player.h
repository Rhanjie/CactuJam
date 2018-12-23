#ifndef CACTUJAM_PLAYER_H
#define CACTUJAM_PLAYER_H

#include <SFML/Graphics.hpp>
#include "../utilities/graphics/ResourceManager.h"
#include "../utilities/graphics/Animation.h"
#include "../utilities/Camera.h"

class Player : public sf::Drawable{
public:
    Player(const std::string& id, Camera* camera, Map* map);

    void update(sf::Vector2f mousePosition);
    void setPosition(sf::Vector2f newPosition);

    const sf::Sprite &getSprite() const;
    void setSprite(const sf::Sprite &sprite);

    float getSpeed() const;
    void setSpeed(float speed);

    void jump();

private:
    sf::Sprite sprite;
    Animation animation;
    Camera* camera = nullptr;
    Map* map = nullptr;

    float speed = 300;
    float velocity = 0;

    int gifts = 10; //HP

    bool isRightCollision();
    bool isLeftCollision();
    bool isUpCollision();
    bool isDownCollision();

    void handleInput(sf::Vector2f mousePosition);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //CACTUJAM_PLAYER_H
