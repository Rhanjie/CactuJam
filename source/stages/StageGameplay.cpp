#include "StageGameplay.h"

StageGameplay::StageGameplay(sf::RenderWindow *window)
    : Stage(window)
    , map(sf::Vector2u(50, 30))
    , player("man1", &camera, &map) {
    camera.getView().setSize(window->getSize().x, window->getSize().y);

    player.setPosition(sf::Vector2f(200, -100));

    //...

    Logger::debug("Stage changed to gameplay!");
}

void StageGameplay::pollEvent(GameManager &gameManager) {
    DeltaTime::get().update();

    while (window->pollEvent(event)) {
        if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::LostFocus)
            isActive = false;

        if (event.type == sf::Event::GainedFocus)
            isActive = true;

        if (isActive) {
            windowMousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window), window->getDefaultView());

            //...
        }

        camera.handleEvent(event);
    }
}

void StageGameplay::serve(GameManager &gameManager) {
    if (isActive) {
        fixedMousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window), camera.getView());
        centerTilePosition = Camera::getMapPosition(sf::Vector2f(camera.getView().getCenter()));

        player.update(fixedMousePosition);

        window->clear(sf::Color(0, 150, 255));

        window->setView(camera.getView());
        map.render(*window);
        window->draw(player);

        window->setView(window->getDefaultView());
        //...

        window->display();
    }
}

