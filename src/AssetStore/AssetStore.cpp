#include "AssetStore.h"

AssetStore::AssetStore(std::shared_ptr<Logger> logger) {
    this->logger = logger;
    this->logger->Log("AssetStore created");
}

AssetStore::~AssetStore() {
    ClearAssets();
    logger->Log("AssetStore destroyed");
}

void AssetStore::ClearAssets() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture.second);
        logger->Log("Removed texture with id = " + texture.first);
    }
    textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer,
                            const std::string& textureId,
                            const std::string& filePath) {
    // TODO convert filepath to texture
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    textures.emplace(textureId, texture);
    logger->Log("New texture with id = " + textureId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& textureId) {
    return textures[textureId];
}