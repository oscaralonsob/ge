#ifndef ASSETSTORE_HPP
#define ASSETSTORE_HPP

#include "../Debug/Events/LogRequestEvent.hpp"
#include "../Events/EventBus.hpp"

#include <SDL2/SDL_ttf.h>
#include <map>
#include <memory>
#include <string>

class AssetStore {
private:
    class SDL_Renderer* renderer;
    std::shared_ptr<EventBus> eventBus;

    std::map<std::string, class SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
    // TODO: CC - create a class that implements TTF so can class forward
    // TODO: map for audio...

public:
    AssetStore(std::shared_ptr<EventBus> eventBus, SDL_Renderer* renderer);
    ~AssetStore();

    void ClearAssets();

    void AddTexture(const std::string& textureId, const std::string& filePath);
    SDL_Texture* GetTexture(const std::string& textureId);

    void AddFont(const std::string& fontId, const std::string& filePath,
                 const int size);
    TTF_Font* GetFont(const std::string& fontId);
};

#endif