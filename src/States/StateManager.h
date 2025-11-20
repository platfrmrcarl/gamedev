#pragma once
#include "GameState.h"
#include <vector>
#include <memory>

class StateManager {
public:
    void PushState(std::shared_ptr<GameState> state);
    void PopState();
    void ChangeState(std::shared_ptr<GameState> state);
    
    void Update(float dt);
    void Render();
    void Clean();

    std::shared_ptr<GameState> GetCurrentState() {
        if (m_GameStates.empty()) return nullptr;
        return m_GameStates.back();
    }

private:
    std::vector<std::shared_ptr<GameState>> m_GameStates;
};
