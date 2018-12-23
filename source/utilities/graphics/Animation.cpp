#include "Animation.h"

Animation::Animation(const ExTexture &_texture)
        : texture(_texture) {
}

void Animation::play() {
    if(frameClock.getElapsedTime() >= frameTime) {
        this->setNextFrame();

        frameClock.restart();
    }
}

void Animation::set(const std::string& id) {
    if (id != currAnimName) {
        if (data.find(id) != data.end()) {
            currAnimName = id;
            currentAnim = data[id].row;
            currentFrame = 0;
            frameTime = data[id].frameTime;
        }
    }
}

void Animation::setNextFrame() {
    currentFrame += 1;

    if (currentFrame > data[currAnimName].col - 1)
        currentFrame = 0;

    unsigned int w = texture.getWFrame();
    unsigned int h = texture.getHFrame();

    int i = 0;
    for(auto sprite : sprites)
        sprite->setTextureRect(sf::IntRect(currentFrame * w, currentAnim * h, w, h));
}

void Animation::add(const std::string& id, int row, int columns, sf::Time frameTime) {
    data[id].row = row;
    data[id].col = columns;
    data[id].frameTime = frameTime;
}

void Animation::addSprite(sf::Sprite* sprite) {
    sprites.push_back(sprite);

    unsigned int w = texture.getWFrame();
    unsigned int h = texture.getHFrame();

    (*(sprites.end() - 1))->setTextureRect(sf::IntRect(currentFrame * w, currentAnim * h, w, h));
}

//TODO: Problem with that method - Freezes application
void Animation::loadAnimationsFromLua(const std::string &id) {
    if (ResourceManager::getRawAttribute(id, "animations") != sol::nil) {
        sol::table animations = ResourceManager::getRawAttribute(id, "animations").as<sol::table>();

        for (const auto &rawPair : animations) {
            int index = 1;
            int columns = 1;
            float frameTime = 1;

            sol::object rawAnimationName = rawPair.first;
            std::string animationName = rawAnimationName.as<std::string>();

            sol::object rawAnimationValues = rawPair.second;
            sol::table animationValues = rawAnimationValues.as<sol::table>();

            //TODO: Improve that code
            int j = 1;
            for (const auto &values : animationValues) {
                sol::object rawValue = values.second;

                switch(j++) {
                    case 1: index = rawValue.as<int>();
                    case 2: columns = rawValue.as<int>();
                    case 3: frameTime = rawValue.as<float>();
                    default: break;
                }
            }

            this->add(animationName, index, columns, sf::seconds(frameTime));

            if (currAnimName.empty())
                this->set(animationName);
        }
    }

    //Set if exist
    this->set("idle");
}

std::string Animation::getCurrAnimName() {
    return currAnimName;
}
