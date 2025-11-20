#include "PlayState.h"
#include "../Core/Engine.h"
#include "../Input/InputManager.h"
#include "../Core/TextureManager.h"
#include "../Core/Camera.h"
#include <iostream>

void PlayState::Enter() {
    std::cout << "Entering PlayState" << std::endl;

    // Load Textures
    TextureManager::GetInstance().Load("player", "assets/player.bmp");
    TextureManager::GetInstance().Load("tiles", "assets/tiles.bmp");

    // Load Level
    m_Level = new Level();
    if (!m_Level->Load("assets/level1.txt")) {
        std::cout << "Failed to load level" << std::endl;
    }
    m_PhysicsWorld.SetLevel(m_Level);

    // Create Player
    m_Player = new GameObject(100, 300, 32, 32, "player");
    m_GameObjects.push_back(m_Player);
    m_PhysicsWorld.AddBody(m_Player->GetRigidBody());

    // Controller
    m_Controller = new PlayerController(m_Player);

    // Camera
    Camera::GetInstance().SetTarget(&m_Player->GetRigidBody()->position);
    Camera::GetInstance().SetLimit(m_Level->GetWidth() * m_Level->GetTileSize(), m_Level->GetHeight() * m_Level->GetTileSize());
}

void PlayState::Exit() {
    for (auto obj : m_GameObjects) {
        delete obj;
    }
    m_GameObjects.clear();
    delete m_Level;
    delete m_Controller;
    TextureManager::GetInstance().Clean();
}

void PlayState::Update(float dt) {
    // InputManager& input = InputManager::GetInstance(); // Not needed here directly anymore if only for player
    // But we might need it for other things later.

    if (m_Controller) m_Controller->Update(dt);

    m_PhysicsWorld.Update(dt);
    Camera::GetInstance().Update(dt);

    for (auto obj : m_GameObjects) {
        obj->Update(dt);
    }
}

void PlayState::Render() {
    if (m_Level) m_Level->Render();
    for (auto obj : m_GameObjects) {
        obj->Render();
    }
}
