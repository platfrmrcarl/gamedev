#include "Engine.h"
#include <iostream>

bool Engine::Init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!m_Window) {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, NULL);
    if (!m_Renderer) {
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    InputManager::GetInstance(); // Initialize InputManager

    m_Running = true;
    return true;
}

void Engine::Clean() {
    m_StateManager.Clean();
    InputManager::GetInstance().Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Engine::Quit() {
    m_Running = false;
}

void Engine::Update() {
    float currentTime = SDL_GetTicks() / 1000.0f;
    float dt = currentTime - m_LastTime;
    m_LastTime = currentTime;

    // Clamp dt to avoid huge jumps if lag occurs
    if (dt > 0.05f) dt = 0.05f;

    m_StateManager.Update(dt);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);

    m_StateManager.Render();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    InputManager::GetInstance().Clean(); // Refresh previous key states
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            Quit();
        }
        // InputManager actually reads state directly from SDL internal array, 
        // but we still need to poll events to update that internal array.
    }
}
