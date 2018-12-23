#include "ResourceManager.h"
#include "../../maps/Map.h"
#include "Animation.h"

void ResourceManager::loadAll() {
    auto auxiliaryTexture = new ExTexture();
    auxiliaryTexture->loadFromFile("assets/default.png");
    textures["default"] = auxiliaryTexture;
    Logger::debug("Texture [default] loaded!");

    script.open_libraries(sol::lib::base);
    script.script_file("assets/tiles.lua");
    script.script_file("assets/characters.lua");
    std::string files[] = {"tiles", "characters"};

    for (int i = 0; i < 2; i++) {
        sol::table table = script[files[i]];

        std::string textureId;
        for (const auto &pair : table) {
            sol::object rawKey = pair.first;
            textureId = rawKey.as<std::string>();

            sol::table argsTable;
            if (script[files[i]][textureId] != sol::nil)
                argsTable = script[files[i]][textureId];

            for (const auto& rawPair : argsTable) {
                sol::object rawArg = rawPair.first;
                sol::object rawValue = rawPair.second;

                if (rawValue != sol::nil)
                    attributes[textureId].insert(std::make_pair(rawArg.as<std::string>(), rawValue));
            }

            if (script[files[i]][textureId]["texture"] != sol::nil) {
                auxiliaryTexture = new ExTexture();
                auxiliaryTexture->loadFromFile(script[files[i]][textureId]["texture"]);
                auxiliaryTexture->init();

                std::string type = "single";
                if (script[files[i]][textureId]["textureType"] != sol::nil)
                    type = script[files[i]][textureId]["textureType"];

                if (type == "multi" || type == "animation") {
                    unsigned int rows = 1;
                    unsigned int cols = 1;

                    if (script[files[i]][textureId]["rows"] != sol::nil)
                        rows = script[files[i]][textureId]["rows"];

                    if (script[files[i]][textureId]["maxColumns"] != sol::nil)
                        cols = script[files[i]][textureId]["maxColumns"];

                    unsigned int wFrame = auxiliaryTexture->getSize().x / cols;
                    unsigned int hFrame = auxiliaryTexture->getSize().y / rows;

                    auxiliaryTexture->createMultiTexture(type, rows, cols, wFrame, hFrame);

                    multiSprite[textureId] = new ManySprites(*auxiliaryTexture);
                    Logger::debug("Multi texture [" + textureId + "] loaded!");
                }

                textures[textureId] = auxiliaryTexture;
                Logger::debug("Texture [" + textureId + "] loaded!");

                if (type == "animation") {
                    if (script[files[i]][textureId]["synchronizedAnim"] != sol::nil) {
                        if ((std::string) script[files[i]][textureId]["synchronizedAnim"] == "true") {
                            if (script[files[i]][textureId]["animations"] != sol::nil) {
                                syncAnimations[textureId] = new Animation(*textures[textureId]);
                                Logger::debug("SyncAnimation [" + textureId + "] loaded!");

                                syncAnimations[textureId]->loadAnimationsFromLua(textureId);
                            }
                        }
                    }
                }

                if (script[files[i]][textureId]["shadowTexture"] != sol::nil) {
                    auxiliaryTexture = new ExTexture();
                    auxiliaryTexture->loadFromFile(script[files[i]][textureId]["shadowTexture"]);
                    auxiliaryTexture->init();
                    textures[textureId + "_shadow"] = auxiliaryTexture;
                    Logger::debug("Texture [" + textureId + "_shadow] loaded!");
                }
            }
        }
    }

    //TODO: Other attributes
    /*attributes[textureId] = config[textureId];
    if (config[textureId]["use_config"] == "true") {
        attributes[textureId].merge(attr[textureId]);
    }*/

    Logger::info("All textures are loaded");
}

ExTexture &ResourceManager::getTexture(std::string id) {
    if (ResourceManager::getInstance().textures.find(id) == ResourceManager::getInstance().textures.end()) {
        Logger::warning("Cannot find texture with id: [" + id + "]");

        return *ResourceManager::getInstance().textures["default"];
    }

    return *ResourceManager::getInstance().textures[id];
}

ManySprites &ResourceManager::getMultiSprite(std::string id) {
    if (ResourceManager::getInstance().multiSprite.find(id) == ResourceManager::getInstance().multiSprite.end()) {
        Logger::warning("Cannot find multi sprite with id: [" + id + "]");

        return *new ManySprites(*ResourceManager::getInstance().textures["default"]);
    }

    return *ResourceManager::getInstance().multiSprite[id];
}

Animation& ResourceManager::getSyncAnimation(std::string id) {
    if (ResourceManager::getInstance().syncAnimations.find(id) == ResourceManager::getInstance().syncAnimations.end()) {
        Logger::warning("Cannot find synchronized animation with id: [" + id + "]");

        return *new Animation(*ResourceManager::getInstance().textures["default"]);
    }

    return *ResourceManager::getInstance().syncAnimations[id];
}

sol::object &ResourceManager::getRawAttribute(const std::string &id, const std::string &attr) {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    if (id.empty() || attr.empty())
        return resourceManager.attributes["default"]["default"];

    if (resourceManager.attributes.find(id) == resourceManager.attributes.end() ||
        resourceManager.attributes[id].find(attr) == resourceManager.attributes[id].end()) {
        //Logger::warning("Cannot find attribute " + attr + " for " + id + " resource");
        return resourceManager.attributes["default"]["default"];
    }

    return resourceManager.attributes[id][attr];
}

ResourceManager &ResourceManager::getInstance() {
    static ResourceManager resourceManager;
    return resourceManager;
}
