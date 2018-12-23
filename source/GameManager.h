#ifndef CACTUJAM_GAMEMANAGER_H
#define CACTUJAM_GAMEMANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "utilities/Logger.h"
#include "utilities/graphics/ResourceManager.h"
#include "stages/Stage.h"

class Stage;
class GameManager {
    friend Stage;

public:
    GameManager(unsigned int w, unsigned int h, const std::string& title);

    void runGame();
    void setStage(Stage* newStage);
    inline Stage* getStage();

protected:
    sf::RenderWindow window;
    sf::ContextSettings settings;

private:
    Stage* stage;
};

#endif //CACTUJAM_GAMEMANAGER_H
