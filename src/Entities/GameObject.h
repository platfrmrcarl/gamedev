#pragma once
#include "../Physics/Physics.h"
#include <SDL3/SDL.h>
#include <string>

class GameObject {
public:
    GameObject(float x, float y, float w, float h, std::string textureID = "");
    ~GameObject() {}

    void Update(float dt);
    void Render();

    RigidBody* GetRigidBody() { return &m_RigidBody; }
    
    void SetFrame(int row, int frame) { m_Row = row; m_Frame = frame; }
    void SetFlip(SDL_FlipMode flip) { m_Flip = flip; }

private:
    RigidBody m_RigidBody;
    float m_Width, m_Height;
    std::string m_TextureID;
    
    int m_Row, m_Frame;
    int m_AnimSpeed;
    SDL_FlipMode m_Flip;
};
