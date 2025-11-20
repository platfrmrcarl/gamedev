#include "PlayerController.h"
#include "InputManager.h"
#include <SDL3/SDL.h>

PlayerController::PlayerController(GameObject* player) 
    : m_Player(player), m_MoveSpeed(500.0f), m_JumpForce(-20000.0f) {}

void PlayerController::Update(float dt) {
    if (!m_Player) return;

    InputManager& input = InputManager::GetInstance();
    RigidBody* rb = m_Player->GetRigidBody();
    Vector2D force(0, 0);

    // Keyboard
    if (input.IsKeyDown(SDL_SCANCODE_A)) {
        force.x -= m_MoveSpeed;
        m_Player->SetFlip(SDL_FLIP_HORIZONTAL);
    }
    if (input.IsKeyDown(SDL_SCANCODE_D)) {
        force.x += m_MoveSpeed;
        m_Player->SetFlip(SDL_FLIP_NONE);
    }
    
    if (input.IsKeyPressed(SDL_SCANCODE_SPACE) && rb->isGrounded) {
        rb->ApplyForce(Vector2D(0, m_JumpForce));
        rb->isGrounded = false;
    }

    // Gamepad
    if (input.GetAxis(0, SDL_GAMEPAD_AXIS_LEFTX) != 0) {
        force.x += input.GetAxis(0, SDL_GAMEPAD_AXIS_LEFTX) * m_MoveSpeed;
        if (force.x > 0) m_Player->SetFlip(SDL_FLIP_NONE);
        if (force.x < 0) m_Player->SetFlip(SDL_FLIP_HORIZONTAL);
    }
    
    if (input.IsButtonDown(0, SDL_GAMEPAD_BUTTON_SOUTH) && rb->isGrounded) {
        rb->ApplyForce(Vector2D(0, m_JumpForce));
        rb->isGrounded = false;
    }

    rb->ApplyForce(force);
}
