#ifndef IZOGAME_STAGE_H
#define IZOGAME_STAGE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "../utilities/Logger.h"
#include "../utilities/graphics/ResourceManager.h"
#include "../GameManager.h"

//TODO: How can I remove this declaration?
class GameManager;

class Stage {
public:
    virtual void pollEvent(GameManager &gameManager) = 0;
    virtual void serve(GameManager &gameManager) = 0;

protected:
    sf::RenderWindow* window;
    sf::Event event;

    bool isActive = true;

    explicit Stage(sf::RenderWindow* window);
};

#endif //IZOGAME_STAGE_H
