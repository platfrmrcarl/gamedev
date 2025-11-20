#pragma once
#include "../Physics/Physics.h"
#include <SDL3/SDL.h>

class Camera {
public:
    static Camera& GetInstance() {
        static Camera instance;
        return instance;
    }

    void Update(float dt);
    void SetTarget(Vector2D* target) { m_Target = target; }
    void SetLimit(int w, int h) { m_SceneWidth = w; m_SceneHeight = h; }

    SDL_Rect GetViewBox() { return m_ViewBox; }
    Vector2D GetPosition() { return Vector2D(m_ViewBox.x, m_ViewBox.y); }

private:
    Camera();
    
    Vector2D* m_Target;
    SDL_Rect m_ViewBox;
    int m_SceneWidth, m_SceneHeight;
};
