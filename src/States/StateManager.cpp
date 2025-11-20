#include "StateManager.h"

void StateManager::PushState(std::shared_ptr<GameState> state) {
    m_GameStates.push_back(state);
    m_GameStates.back()->Enter();
}

void StateManager::PopState() {
    if (!m_GameStates.empty()) {
        m_GameStates.back()->Exit();
        m_GameStates.pop_back();
    }
}

void StateManager::ChangeState(std::shared_ptr<GameState> state) {
    if (!m_GameStates.empty()) {
        if (m_GameStates.back()->GetStateID() == state->GetStateID()) {
            return; // Do nothing if same state
        }
        m_GameStates.back()->Exit();
        m_GameStates.pop_back();
    }
    m_GameStates.push_back(state);
    m_GameStates.back()->Enter();
}

void StateManager::Update(float dt) {
    if (!m_GameStates.empty()) {
        m_GameStates.back()->Update(dt);
    }
}

void StateManager::Render() {
    if (!m_GameStates.empty()) {
        m_GameStates.back()->Render();
    }
}

void StateManager::Clean() {
    while (!m_GameStates.empty()) {
        m_GameStates.back()->Exit();
        m_GameStates.pop_back();
    }
}
