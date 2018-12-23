#include "Player.h"

Player::Player(const std::string &id, Camera* camera, Map* map)
    : animation(ResourceManager::getTexture(id)){
    animation.loadAnimationsFromLua(id);

    sprite.setTexture(ResourceManager::getTexture(id));
    animation.addSprite(&sprite);

    this->camera = camera;
    this->map = map;

    sprite.setPosition(this->camera->getView().getCenter());
}

void Player::update(sf::Vector2f mousePosition) {
    this->handleInput(mousePosition);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        //this->attack();
        //change animation;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        MapTile* clickedTile = map->getTileOnPixelPos(mousePosition);
        int index = map->getTileIndexOnPixelPos(mousePosition);

        map->changeTileByIndex(index, "air", MapTile::NORMAL); //TODO: Chosen id
    }

    animation.play();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}

void Player::setPosition(sf::Vector2f newPosition) {
    camera->getView().setCenter(newPosition);

    sprite.setPosition(newPosition);
}

void Player::handleInput(sf::Vector2f mousePosition) {
    if (velocity < 0)
        this->isUpCollision();

    if (!this->isDownCollision()) {
        velocity += 1800 * DeltaTime::getDt();
    }

    camera->getView().move(0, velocity * DeltaTime::getDt());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !this->isRightCollision())
        camera->getView().move(speed * DeltaTime::getDt(), 0);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !this->isLeftCollision())
        camera->getView().move(-speed * DeltaTime::getDt(), 0);

    sprite.setPosition(camera->getView().getCenter());
}

const sf::Sprite &Player::getSprite() const {
    return sprite;
}

void Player::setSprite(const sf::Sprite &sprite) {
    Player::sprite = sprite;
}

float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float speed) {
    Player::speed = speed;
}

void Player::jump() {
    velocity = -800;
}

bool Player::isRightCollision() {
    float afterMovePos = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width + speed * DeltaTime::getDt();

    MapTile* tile1 = map->getTileOnPixelPos(sf::Vector2f(afterMovePos, sprite.getPosition().y));
    MapTile* tile2 = map->getTileOnPixelPos(sf::Vector2f(afterMovePos, sprite.getPosition().y + sprite.getGlobalBounds().height / 2));
    MapTile* tile3 = map->getTileOnPixelPos(sf::Vector2f(afterMovePos, sprite.getPosition().y + sprite.getGlobalBounds().height - 1));

    if (tile1->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(tile1->getPosition().x - sprite.getGlobalBounds().width, camera->getView().getCenter().y));

        return true;
    }

    else if (tile2->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(tile2->getPosition().x - sprite.getGlobalBounds().width, camera->getView().getCenter().y));

        return true;
    }

    else if (tile3->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(tile3->getPosition().x - sprite.getGlobalBounds().width, camera->getView().getCenter().y));

        return true;
    }

    else return false;
}

bool Player::isLeftCollision() {
    float afterMovePos = sprite.getGlobalBounds().left - speed * DeltaTime::getDt();

    MapTile* tile1 = map->getTileOnPixelPos(sf::Vector2f(afterMovePos, sprite.getPosition().y));
    MapTile* tile2 = map->getTileOnPixelPos(sf::Vector2f(afterMovePos, sprite.getPosition().y + sprite.getGlobalBounds().height / 2));
    MapTile* tile3 = map->getTileOnPixelPos(sf::Vector2f(afterMovePos, sprite.getPosition().y + sprite.getGlobalBounds().height - 1));

    if (tile1->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(tile1->getPosition().x + tile1->getSprite().getGlobalBounds().width, camera->getView().getCenter().y));

        return true;
    }

    else if (tile2->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(tile2->getPosition().x + tile2->getSprite().getGlobalBounds().width, camera->getView().getCenter().y));

        return true;
    }

    else if (tile3->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(tile3->getPosition().x + tile3->getSprite().getGlobalBounds().width, camera->getView().getCenter().y));

        return true;
    }

    else return false;
}

bool Player::isUpCollision() {
    float afterMovePos = sprite.getGlobalBounds().top - speed * DeltaTime::getDt();

    MapTile* tile1 = map->getTileOnPixelPos(sf::Vector2f(sprite.getPosition().x, afterMovePos));
    MapTile* tile2 = map->getTileOnPixelPos(sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width - 1, afterMovePos));


    if (tile1->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(camera->getView().getCenter().x, tile1->getPosition().y + tile1->getSprite().getGlobalBounds().height));

        velocity = 0;
        return true;
    }

    else if (tile2->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(camera->getView().getCenter().x, tile2->getPosition().y + tile2->getSprite().getGlobalBounds().height));

        velocity = 0;
        return true;
    }
}

bool Player::isDownCollision() {
    float afterMovePos = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height + speed * DeltaTime::getDt();

    MapTile* tile1 = map->getTileOnPixelPos(sf::Vector2f(sprite.getPosition().x, afterMovePos));
    MapTile* tile2 = map->getTileOnPixelPos(sf::Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width - 1, afterMovePos));

    if (tile1->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(camera->getView().getCenter().x, tile1->getPosition().y - sprite.getGlobalBounds().height));

        velocity = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            this->jump();

        return true;
    }

    else if (tile2->getType() == MapTile::OBSTACLE) {
        this->setPosition(sf::Vector2f(camera->getView().getCenter().x, tile2->getPosition().y - sprite.getGlobalBounds().height));

        velocity = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            this->jump();

        return true;
    }

    else return false;
}