#include "GameManager.h"

#include "stages/StageMenu.h"
#include "stages/StageGameplay.h"

GameManager::GameManager(unsigned int w, unsigned int h, const std::string& title) {
    Logger::setDebugMode(true);

    ResourceManager::getInstance().loadAll();

    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode(w, h), title, sf::Style::Close, settings); // sf::Style::Close
    stage = new StageMenu(&window);

    Logger::info("Window was created!");
}

void GameManager::runGame() {
    while(window.isOpen()) {
        stage->pollEvent(*this);
        stage->serve(*this);
    }
};

void GameManager::setStage(Stage* newStage) {
    stage = newStage;
}

Stage* GameManager::getStage() {
    return stage;
}

