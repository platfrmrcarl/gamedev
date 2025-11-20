#pragma once
#include "../Entities/GameObject.h"

class PlayerController {
public:
    PlayerController(GameObject* player);
    void Update(float dt);

private:
    GameObject* m_Player;
    float m_MoveSpeed;
    float m_JumpForce;
};
