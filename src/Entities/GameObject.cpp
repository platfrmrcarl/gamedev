#include "GameObject.h"
#include "../Core/TextureManager.h"
#include "../Core/Camera.h"
#include "../Core/Engine.h"

GameObject::GameObject(float x, float y, float w, float h, std::string textureID) 
    : m_Width(w), m_Height(h), m_TextureID(textureID), m_Row(1), m_Frame(0), m_AnimSpeed(100), m_Flip(SDL_FLIP_NONE)
{
    m_RigidBody.position = Vector2D(x, y);
    m_RigidBody.collider.type = AABB;
    m_RigidBody.collider.width = w;
    m_RigidBody.collider.height = h;
    m_RigidBody.collider.offset = Vector2D(0, 0);
}

void GameObject::Update(float dt) {
    // Animation logic
    m_Frame = (int)((SDL_GetTicks() / m_AnimSpeed) % 6); // 6 frames for now
}

void GameObject::Render() {
    Vector2D camPos = Camera::GetInstance().GetPosition();
    int drawX = (int)(m_RigidBody.position.x - camPos.x);
    int drawY = (int)(m_RigidBody.position.y - camPos.y);

    if (m_TextureID != "") {
        TextureManager::GetInstance().DrawFrame(m_TextureID, drawX, drawY, m_Width, m_Height, m_Row, m_Frame, m_Flip);
    } else {
        // Fallback rect
        SDL_FRect rect = { (float)drawX, (float)drawY, m_Width, m_Height };
        SDL_SetRenderDrawColor(Engine::GetInstance().GetRenderer(), 255, 0, 255, 255);
        SDL_RenderFillRect(Engine::GetInstance().GetRenderer(), &rect);
    }
}
