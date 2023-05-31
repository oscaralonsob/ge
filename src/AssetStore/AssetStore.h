#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include "../Logger/Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <memory>
#include <string>

class AssetStore {
private:
    std::shared_ptr<Logger> logger;

    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;
    // TODO: map for audio...

public:
    AssetStore(std::shared_ptr<Logger> logger);
    ~AssetStore();

    void ClearAssets();

    void AddTexture(SDL_Renderer* renderer, const std::string& textureId,
                    const std::string& filePath);
    SDL_Texture* GetTexture(const std::string& textureId);

    void AddFont(const std::string& fontId, const std::string& filePath,
                 const int size);
    TTF_Font* GetFont(const std::string& fontId);
};

#endif