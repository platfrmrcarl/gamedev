#pragma once
#include "../Physics/Physics.h"
#include "../Graphics/Sprite.h"

class GameObject {
public:
    GameObject(float x, float y, float w, float h, std::string textureID = "");
    ~GameObject();

    void Update(float dt);
    void Render();

    RigidBody* GetRigidBody() { return &m_RigidBody; }
    Sprite* GetSprite() { return m_Sprite; }
    
    void SetFlip(SDL_FlipMode flip);

private:
    RigidBody m_RigidBody;
    float m_Width, m_Height;
    Sprite* m_Sprite;
};
