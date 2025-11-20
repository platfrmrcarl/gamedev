#include "Camera.h"
#include "Engine.h"

Camera::Camera() : m_Target(nullptr), m_SceneWidth(0), m_SceneHeight(0) {
    m_ViewBox = { 0, 0, 1280, 720 };
}

void Camera::Update(float dt) {
    if (m_Target) {
        // Center camera on target
        m_ViewBox.x = (int)(m_Target->x) - 1280 / 2;
        m_ViewBox.y = (int)(m_Target->y) - 720 / 2;

        // Clamp to scene bounds
        if (m_ViewBox.x < 0) m_ViewBox.x = 0;
        if (m_ViewBox.y < 0) m_ViewBox.y = 0;
        if (m_ViewBox.x > m_SceneWidth - m_ViewBox.w) m_ViewBox.x = m_SceneWidth - m_ViewBox.w;
        if (m_ViewBox.y > m_SceneHeight - m_ViewBox.h) m_ViewBox.y = m_SceneHeight - m_ViewBox.h;
    }
}
