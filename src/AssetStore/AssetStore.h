#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <memory>
#include "../Logger/Logger.h"

class AssetStore {
    private:
        std::shared_ptr<Logger> logger;

        std::map<std::string, SDL_Texture*> textures;
        //TODO: map for fonts, audio...

    public:
        AssetStore(std::shared_ptr<Logger> logger);
        ~AssetStore();
        
        void ClearAssets();
        void AddTexture(SDL_Renderer* renderer, const std::string& textureId, const std::string& filePath);
        SDL_Texture* GetTexture(const std::string& textureId);
};

#endif