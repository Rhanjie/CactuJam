#ifndef IZOGAME_STAGEMENU_H
#define IZOGAME_STAGEMENU_H

#include "Stage.h"
#include "StageGameplay.h"

class StageMenu: public Stage {
public:
    explicit StageMenu(sf::RenderWindow* window);

    void pollEvent(GameManager &gameManager) override;
    void serve(GameManager &gameManager) override;

private:
    //...

};


#endif //IZOGAME_STAGEMENU_H
