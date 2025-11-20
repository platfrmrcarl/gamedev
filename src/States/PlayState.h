#pragma once
#include "GameState.h"
#include "../Entities/GameObject.h"
#include "../Physics/Physics.h"
#include "../Core/Level.h"
#include <vector>

#include "../Input/PlayerController.h"

class PlayState : public GameState {
public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update(float dt) override;
    virtual void Render() override;
    virtual std::string GetStateID() const override { return "PLAY"; }

private:
    std::vector<GameObject*> m_GameObjects;
    PhysicsWorld m_PhysicsWorld;
    GameObject* m_Player;
    Level* m_Level;
    PlayerController* m_Controller;
};
