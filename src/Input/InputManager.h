#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class InputManager {
public:
    static InputManager& GetInstance() {
        static InputManager instance;
        return instance;
    }

    void Update();
    void Clean();

    // Keyboard
    bool IsKeyDown(SDL_Scancode key);
    bool IsKeyPressed(SDL_Scancode key);
    bool IsKeyReleased(SDL_Scancode key);

    // Gamepad
    void OpenGamepads();
    void CloseGamepads();
    bool IsButtonDown(int gamepadID, int button);
    float GetAxis(int gamepadID, int axis); // Returns -1.0 to 1.0

private:
    InputManager();
    ~InputManager();

    const bool* m_KeyboardStates;
    std::vector<Uint8> m_PrevKeyboardStates;
    int m_KeyLength;

    std::vector<SDL_Gamepad*> m_Gamepads;
    
    // Helper to update previous keyboard state
    void UpdatePrevInput();
};
