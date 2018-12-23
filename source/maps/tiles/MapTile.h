#ifndef IZOGAME_MAPTILE_H
#define IZOGAME_MAPTILE_H

#include "../MapRenderedObject.h"


class MapTile : public MapRenderedObject {
public:
    enum Type{NORMAL, OBSTACLE, TRAP};
    MapTile(const std::string &id, Type type, const ExTexture &texture, sf::Vector2f position);

    void update() override;

    bool getBuildBlock();

    Type getType() const;
    void setType(Type type);

protected:
    bool buildBlock = false;
    int height = 0;
    Type type = NORMAL;

protected:

    void loadLuaValues(const ExTexture &texture) override;
};

#endif //IZOGAME_MAPTILE_H
