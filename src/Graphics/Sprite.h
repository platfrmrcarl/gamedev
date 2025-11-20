#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <map>
#include "Animation.h"

class Sprite {
public:
    Sprite(std::string textureID, int width, int height);
    ~Sprite() {}

    void Update(float dt);
    void Render(int x, int y);

    void AddAnimation(std::string name, int row, int frameCount, int speed);
    void Play(std::string name);
    void SetFlip(SDL_FlipMode flip) { m_Flip = flip; }

private:
    std::string m_TextureID;
    int m_Width, m_Height;
    SDL_FlipMode m_Flip;

    std::map<std::string, Animation> m_Animations;
    Animation m_CurrentAnimation;
    int m_CurrentFrame;
};
