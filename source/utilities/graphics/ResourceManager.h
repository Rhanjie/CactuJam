#ifndef IZOGAME_RESOURCEMANAGER_H
#define IZOGAME_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include "sol.hpp"
#include "../Logger.h"
#include "ExTexture.h"
#include "ManySprites.h"

class Animation;
class ResourceManager {
public:
    static ExTexture &getTexture(std::string id);
    static ManySprites &getMultiSprite(std::string id);
    static Animation &getSyncAnimation(std::string id);
    static sol::object &getRawAttribute(const std::string &id, const std::string &attr);

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator = (const ResourceManager&) = delete;
    static ResourceManager &getInstance();

    void loadAll();

private:
    std::map<std::string, ExTexture*> textures;
    std::map<std::string, ManySprites*> multiSprite;
    std::map<std::string, Animation*> syncAnimations;
    std::map<std::string, std::map<std::string, sol::object>> attributes;

    sol::state script;

    ResourceManager() = default;

};

#endif //IZOGAME_RESOURCEMANAGER_H
