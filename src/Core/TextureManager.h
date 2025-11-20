#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <map>

class TextureManager {
public:
    static TextureManager& GetInstance() {
        static TextureManager instance;
        return instance;
    }

    bool Load(std::string id, std::string filename);
    void Drop(std::string id);
    void Clean();

    void Draw(std::string id, int x, int y, int width, int height, SDL_FlipMode flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_FlipMode flip = SDL_FLIP_NONE);

private:
    TextureManager() {}
    ~TextureManager() { Clean(); }

    std::map<std::string, SDL_Texture*> m_TextureMap;
};
