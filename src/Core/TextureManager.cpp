#include "TextureManager.h"
#include "Engine.h"
#include <iostream>

bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
    if (!surface) {
        std::cout << "Failed to load texture: " << filename << " " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance().GetRenderer(), surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_FlipMode flip) {
    SDL_FRect srcRect = { 0, 0, (float)width, (float)height };
    // We need to account for camera here eventually, but for now raw drawing
    // Actually, Camera transform should happen in the call or we pass a camera offset.
    // Let's keep it simple: Draw receives WORLD coordinates, but we need to subtract camera.
    // However, TextureManager is usually low level. Let's pass screen coordinates to it.
    SDL_FRect dstRect = { (float)x, (float)y, (float)width, (float)height };
    SDL_RenderTextureRotated(Engine::GetInstance().GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, NULL, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_FlipMode flip) {
    SDL_FRect srcRect = { (float)width * frame, (float)height * (row - 1), (float)width, (float)height };
    SDL_FRect dstRect = { (float)x, (float)y, (float)width, (float)height };
    SDL_RenderTextureRotated(Engine::GetInstance().GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, NULL, flip);
}

void TextureManager::Drop(std::string id) {
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean() {
    for (auto& tex : m_TextureMap) {
        SDL_DestroyTexture(tex.second);
    }
    m_TextureMap.clear();
}
