#include "StageMenu.h"

StageMenu::StageMenu(sf::RenderWindow *window): Stage(window) {
    Logger::debug("Stage changed to menu!");
}

void StageMenu::pollEvent(GameManager &gameManager) {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void StageMenu::serve(GameManager &gameManager) {
    //TODO: Add menu
    gameManager.setStage(new StageGameplay(window));

    /*window->clear(sf::Color(0, 150, 255));
    window->display();*/
}