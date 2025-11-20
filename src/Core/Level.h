#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>

struct TileLayer {
    std::vector<std::vector<int>> tilemap;
};

class Level {
public:
    bool Load(std::string fileName);
    void Render();
    
    int GetTileAt(int x, int y); // Returns tile ID
    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }
    int GetTileSize() { return m_TileSize; }

private:
    int m_Width, m_Height, m_TileSize;
    TileLayer m_Layer;
    std::string m_TextureID;
};
