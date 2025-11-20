#include "GameObject.h"
#include "../Core/TextureManager.h"
#include "../Core/Camera.h"
#include "../Core/Engine.h"

GameObject::GameObject(float x, float y, float w, float h, std::string textureID) 
    : m_Width(w), m_Height(h)
{
    m_RigidBody.position = Vector2D(x, y);
    m_RigidBody.collider.type = AABB;
    m_RigidBody.collider.width = w;
    m_RigidBody.collider.height = h;
    m_RigidBody.collider.offset = Vector2D(0, 0);

    if (!textureID.empty()) {
        m_Sprite = new Sprite(textureID, (int)w, (int)h);
    } else {
        m_Sprite = nullptr;
    }
}

GameObject::~GameObject() {
    if (m_Sprite) delete m_Sprite;
}

void GameObject::Update(float dt) {
    if (m_Sprite) m_Sprite->Update(dt);
}

void GameObject::Render() {
    Vector2D camPos = Camera::GetInstance().GetPosition();
    int drawX = (int)(m_RigidBody.position.x - camPos.x);
    int drawY = (int)(m_RigidBody.position.y - camPos.y);

    if (m_Sprite) {
        m_Sprite->Render(drawX, drawY);
    } else {
        // Fallback rect
        SDL_FRect rect = { (float)drawX, (float)drawY, m_Width, m_Height };
        SDL_SetRenderDrawColor(Engine::GetInstance().GetRenderer(), 255, 0, 255, 255);
        SDL_RenderFillRect(Engine::GetInstance().GetRenderer(), &rect);
    }
}

void GameObject::SetFlip(SDL_FlipMode flip) {
    if (m_Sprite) m_Sprite->SetFlip(flip);
}
