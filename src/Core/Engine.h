#pragma once
#include <SDL3/SDL.h>
#include "States/StateManager.h"
#include "Input/InputManager.h"

class Engine {
public:
    static Engine& GetInstance() {
        static Engine instance;
        return instance;
    }

    bool Init(const char* title, int width, int height);
    void Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    bool IsRunning() { return m_Running; }

    SDL_Renderer* GetRenderer() { return m_Renderer; }
    SDL_Window* GetWindow() { return m_Window; }
    StateManager& GetStateManager() { return m_StateManager; }

private:
    Engine() {}
    ~Engine() {}

    bool m_Running;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    StateManager m_StateManager;
    
    float m_LastTime = 0.0f;
};
