#include "AssetStore.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

AssetStore::AssetStore(std::shared_ptr<EventBus> eventBus,
                       SDL_Renderer* renderer) {
    this->eventBus = eventBus;
    this->renderer = renderer;
    this->eventBus->EmitEvent<LogRequestEvent>("AssetStore created");
}

AssetStore::~AssetStore() {
    ClearAssets();
    eventBus->EmitEvent<LogRequestEvent>("AssetStore destroyed");
}

void AssetStore::ClearAssets() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture.second);
        eventBus->EmitEvent<LogRequestEvent>("Removed texture with id = " +
                                             texture.first);
    }
    textures.clear();

    for (auto font : fonts) {
        TTF_CloseFont(font.second);
        eventBus->EmitEvent<LogRequestEvent>("Removed texture with id = " +
                                             font.first);
    }
    fonts.clear();
}

void AssetStore::AddTexture(const std::string& textureId,
                            const std::string& filePath) {
    // TODO convert filepath to texture
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    textures.emplace(textureId, texture);
    eventBus->EmitEvent<LogRequestEvent>("New texture with id = " + textureId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& textureId) {
    return textures[textureId];
}

// TODO: create texture directly?
void AssetStore::AddFont(const std::string& fontId, const std::string& filePath,
                         const int size) {
    fonts.emplace(fontId, TTF_OpenFont(filePath.c_str(), size));
    eventBus->EmitEvent<LogRequestEvent>("New font with id = " + fontId);
}

TTF_Font* AssetStore::GetFont(const std::string& fontId) {
    return fonts[fontId];
}