#include "Sprite.h"
#include "../Core/TextureManager.h"

Sprite::Sprite(std::string textureID, int width, int height)
    : m_TextureID(textureID), m_Width(width), m_Height(height), m_Flip(SDL_FLIP_NONE), m_CurrentFrame(0) 
{
    // Default animation if none
    m_CurrentAnimation = Animation("default", 1, 1, 100);
}

void Sprite::AddAnimation(std::string name, int row, int frameCount, int speed) {
    m_Animations[name] = Animation(name, row, frameCount, speed);
}

void Sprite::Play(std::string name) {
    if (m_CurrentAnimation.name != name) {
        m_CurrentAnimation = m_Animations[name];
        m_CurrentFrame = 0;
    }
}

void Sprite::Update(float dt) {
    if (m_CurrentAnimation.speed > 0) {
        m_CurrentFrame = (SDL_GetTicks() / m_CurrentAnimation.speed) % m_CurrentAnimation.frameCount;
    }
}

void Sprite::Render(int x, int y) {
    TextureManager::GetInstance().DrawFrame(m_TextureID, x, y, m_Width, m_Height, m_CurrentAnimation.row, m_CurrentFrame, m_Flip);
}
