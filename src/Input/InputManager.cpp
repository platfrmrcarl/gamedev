#include "InputManager.h"

InputManager::InputManager() {
    m_KeyboardStates = SDL_GetKeyboardState(&m_KeyLength);
    m_PrevKeyboardStates.resize(m_KeyLength);
    OpenGamepads();
}

InputManager::~InputManager() {
    CloseGamepads();
}

void InputManager::OpenGamepads() {
    int numJoysticks = 0;
    SDL_JoystickID* joysticks = SDL_GetJoysticks(&numJoysticks);
    if (joysticks) {
        for (int i = 0; i < numJoysticks; i++) {
            if (SDL_IsGamepad(joysticks[i])) {
                SDL_Gamepad* pad = SDL_OpenGamepad(joysticks[i]);
                if (pad) {
                    m_Gamepads.push_back(pad);
                    std::cout << "Opened Gamepad: " << SDL_GetGamepadName(pad) << std::endl;
                }
            }
        }
        SDL_free(joysticks);
    }
}

void InputManager::CloseGamepads() {
    for (auto pad : m_Gamepads) {
        SDL_CloseGamepad(pad);
    }
    m_Gamepads.clear();
}

void InputManager::Update() {
    // SDL_PumpEvents is called by SDL_PollEvent in the main loop, 
    // so we just need to update our previous state at the end of the frame
    // or beginning. Ideally, we copy current to previous BEFORE processing new events if we were doing manual pumping,
    // but since SDL updates the internal array automatically, we need to handle "Pressed" logic carefully.
    // Actually, standard pattern: Update() called at start of frame.
}

void InputManager::Clean() {
    // Update previous state for next frame
    if (m_KeyLength > 0) {
        memcpy(m_PrevKeyboardStates.data(), m_KeyboardStates, m_KeyLength);
    }
}

bool InputManager::IsKeyDown(SDL_Scancode key) {
    if (key < 0 || key >= m_KeyLength) return false;
    return m_KeyboardStates[key];
}

bool InputManager::IsKeyPressed(SDL_Scancode key) {
    if (key < 0 || key >= m_KeyLength) return false;
    return m_KeyboardStates[key] && !m_PrevKeyboardStates[key];
}

bool InputManager::IsKeyReleased(SDL_Scancode key) {
    if (key < 0 || key >= m_KeyLength) return false;
    return !m_KeyboardStates[key] && m_PrevKeyboardStates[key];
}

bool InputManager::IsButtonDown(int gamepadID, int button) {
    if (gamepadID < 0 || gamepadID >= m_Gamepads.size()) return false;
    return SDL_GetGamepadButton(m_Gamepads[gamepadID], (SDL_GamepadButton)button);
}

float InputManager::GetAxis(int gamepadID, int axis) {
    if (gamepadID < 0 || gamepadID >= m_Gamepads.size()) return 0.0f;
    Sint16 value = SDL_GetGamepadAxis(m_Gamepads[gamepadID], (SDL_GamepadAxis)axis);
    // Deadzone handling could go here
    if (abs(value) < 8000) return 0.0f;
    return (float)value / 32767.0f;
}
