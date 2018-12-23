#include "ManySprites.h"

ManySprites::ManySprites(const ExTexture &texture) {
    sprites.resize(texture.getRows());

    for(int y = 0; y < texture.getRows(); y++) {
        sprites[y].resize(texture.getColumns());

        for(int x = 0; x < texture.getColumns(); x++) {
            sprites[y][x] = sf::Sprite(texture);

            int w = texture.getWFrame();
            int h = texture.getHFrame();

            sprites[y][x].setTextureRect(sf::IntRect(x * w, y * h, w, h));
        }
    }
}

sf::Sprite &ManySprites::getRandomSprite() {
    int y = rand() % sprites.size();
    int x = rand() % sprites[0].size();

    return sprites[y][x];
}

sf::Sprite &ManySprites::getSprite(int x, int y) {
    if (y <= sprites.size() - 1) {
        if (x <= sprites[y].size() - 1) {
            return sprites[y][x];
        }

        else return sprites[y][sprites[y].size() - 1];
    }

    else return sprites[sprites.size() - 1][0];
}


