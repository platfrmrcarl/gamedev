#include "Core/Engine.h"
#include "States/PlayState.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (!Engine::GetInstance().Init("2D Game Engine", 1280, 720)) {
        std::cerr << "Failed to initialize engine." << std::endl;
        return -1;
    }

    Engine::GetInstance().GetStateManager().PushState(std::make_shared<PlayState>());

    while (Engine::GetInstance().IsRunning()) {
        Engine::GetInstance().Events();
        Engine::GetInstance().Update();
        Engine::GetInstance().Render();
    }

    Engine::GetInstance().Clean();
    return 0;
}
