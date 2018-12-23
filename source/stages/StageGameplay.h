#ifndef IZOGAME_STAGEGAMEPLAY_H
#define IZOGAME_STAGEGAMEPLAY_H

#include "Stage.h"
#include "StageMenu.h"
#include "../utilities/Camera.h"
#include "../maps/Map.h"
#include "../characters/Player.h"
#include "sol.hpp"

class StageGameplay: public Stage {
public:
    explicit StageGameplay(sf::RenderWindow* window);

    void pollEvent(GameManager &gameManager) override;
    void serve(GameManager &gameManager) override;

private:
    //Hud hud;
    Map map;

    Camera camera;
    Player player;

    sf::Vector2f fixedMousePosition;
    sf::Vector2f windowMousePosition;
    sf::Vector2i centerTilePosition;

};

#endif //IZOGAME_STAGEGAMEPLAY_H
