#include "Level.h"
#include "TextureManager.h"
#include "Camera.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Level::Load(std::string fileName) {
    // Simple format:
    // texture_id
    // tile_size
    // width height
    // row1...
    // row2...
    
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to open level file: " << fileName << std::endl;
        return false;
    }

    file >> m_TextureID;
    file >> m_TileSize;
    file >> m_Width >> m_Height;

    m_Layer.tilemap.resize(m_Height);
    for (int i = 0; i < m_Height; ++i) {
        m_Layer.tilemap[i].resize(m_Width);
        for (int j = 0; j < m_Width; ++j) {
            file >> m_Layer.tilemap[i][j];
        }
    }
    
    file.close();
    return true;
}

void Level::Render() {
    Vector2D camPos = Camera::GetInstance().GetPosition();
    int startX = (int)(camPos.x / m_TileSize);
    int startY = (int)(camPos.y / m_TileSize);
    int endX = startX + (1280 / m_TileSize) + 2;
    int endY = startY + (720 / m_TileSize) + 2;

    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > m_Width) endX = m_Width;
    if (endY > m_Height) endY = m_Height;

    for (int i = startY; i < endY; ++i) {
        for (int j = startX; j < endX; ++j) {
            int id = m_Layer.tilemap[i][j];
            if (id == 0) continue; // Air

            // Draw tile (Assuming tileset is 1 row for simplicity, or calculate row/col)
            // Let's assume tileset is 10 tiles wide
            int row = (id - 1) / 10;
            int col = (id - 1) % 10;
            
            // Adjust for camera
            int drawX = (j * m_TileSize) - (int)camPos.x;
            int drawY = (i * m_TileSize) - (int)camPos.y;

            TextureManager::GetInstance().DrawFrame(m_TextureID, drawX, drawY, m_TileSize, m_TileSize, row + 1, col);
        }
    }
}

int Level::GetTileAt(int x, int y) {
    int col = x / m_TileSize;
    int row = y / m_TileSize;

    if (col < 0 || col >= m_Width || row < 0 || row >= m_Height) return 0;
    return m_Layer.tilemap[row][col];
}
