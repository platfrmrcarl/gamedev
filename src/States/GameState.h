#pragma once
#include <string>

class StateManager; // Forward declaration

class GameState {
public:
    virtual ~GameState() {}
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual std::string GetStateID() const = 0;
};
