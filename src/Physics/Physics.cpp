#include "Physics.h"
#include "../Core/Level.h"
#include <iostream>

void PhysicsWorld::AddBody(RigidBody* body) {
    m_Bodies.push_back(body);
}

void PhysicsWorld::RemoveBody(RigidBody* body) {
    m_Bodies.erase(std::remove(m_Bodies.begin(), m_Bodies.end(), body), m_Bodies.end());
}

void PhysicsWorld::Update(float dt) {
    Vector2D gravity(0, 980.0f); // Gravity

    for (auto body : m_Bodies) {
        if (!body->isStatic) {
            body->ApplyForce(gravity * body->mass);
        }
        body->Update(dt);
        
        if (m_Level && !body->isStatic) {
            ResolveMapCollision(body);
        }
    }

    for (size_t i = 0; i < m_Bodies.size(); ++i) {
        for (size_t j = i + 1; j < m_Bodies.size(); ++j) {
            RigidBody* a = m_Bodies[i];
            RigidBody* b = m_Bodies[j];
            
            if (CheckCollision(a, b)) {
                ResolveCollision(a, b);
            }
        }
    }
}

void PhysicsWorld::ResolveMapCollision(RigidBody* body) {
    body->isGrounded = false;
    int tileSize = m_Level->GetTileSize();
    
    // Check corners
    float x = body->position.x + body->collider.offset.x;
    float y = body->position.y + body->collider.offset.y;
    float w = body->collider.width;
    float h = body->collider.height;

    // Check bottom (Ground)
    int tileBL = m_Level->GetTileAt((int)x + 2, (int)(y + h));
    int tileBR = m_Level->GetTileAt((int)(x + w) - 2, (int)(y + h));

    if (tileBL != 0 || tileBR != 0) {
        body->position.y = (float)(((int)(y + h) / tileSize) * tileSize) - h - body->collider.offset.y;
        body->velocity.y = 0;
        body->isGrounded = true;
    }

    // Check top (Ceiling)
    int tileTL = m_Level->GetTileAt((int)x + 2, (int)y);
    int tileTR = m_Level->GetTileAt((int)(x + w) - 2, (int)y);

    if (tileTL != 0 || tileTR != 0) {
        body->position.y = (float)(((int)y / tileSize) * tileSize) + tileSize - body->collider.offset.y;
        body->velocity.y = 0;
    }

    // Check Right
    int tileTR_S = m_Level->GetTileAt((int)(x + w), (int)y + 2);
    int tileBR_S = m_Level->GetTileAt((int)(x + w), (int)(y + h) - 2);

    if (tileTR_S != 0 || tileBR_S != 0) {
        body->position.x = (float)(((int)(x + w) / tileSize) * tileSize) - w - body->collider.offset.x;
        body->velocity.x = 0;
    }

    // Check Left
    int tileTL_S = m_Level->GetTileAt((int)x, (int)y + 2);
    int tileBL_S = m_Level->GetTileAt((int)x, (int)(y + h) - 2);

    if (tileTL_S != 0 || tileBL_S != 0) {
        body->position.x = (float)(((int)x / tileSize) * tileSize) + tileSize - body->collider.offset.x;
        body->velocity.x = 0;
    }
}

bool PhysicsWorld::CheckCollision(RigidBody* a, RigidBody* b) {
    Vector2D posA = a->position + a->collider.offset;
    Vector2D posB = b->position + b->collider.offset;

    if (a->collider.type == AABB && b->collider.type == AABB) {
        return (posA.x < posB.x + b->collider.width &&
                posA.x + a->collider.width > posB.x &&
                posA.y < posB.y + b->collider.height &&
                posA.y + a->collider.height > posB.y);
    }
    return false;
}

void PhysicsWorld::ResolveCollision(RigidBody* a, RigidBody* b) {
    // Simple AABB resolution (same as before)
    if (a->isStatic && b->isStatic) return;

    Vector2D posA = a->position + a->collider.offset;
    Vector2D posB = b->position + b->collider.offset;

    float overlapX = std::min(posA.x + a->collider.width, posB.x + b->collider.width) - std::max(posA.x, posB.x);
    float overlapY = std::min(posA.y + a->collider.height, posB.y + b->collider.height) - std::max(posA.y, posB.y);

    if (overlapX < overlapY) {
        if (posA.x < posB.x) {
            if(!a->isStatic) a->position.x -= overlapX * 0.5f;
            if(!b->isStatic) b->position.x += overlapX * 0.5f;
        } else {
            if(!a->isStatic) a->position.x += overlapX * 0.5f;
            if(!b->isStatic) b->position.x -= overlapX * 0.5f;
        }
        if(!a->isStatic) a->velocity.x = 0;
        if(!b->isStatic) b->velocity.x = 0;
    } else {
        if (posA.y < posB.y) {
            if(!a->isStatic) a->position.y -= overlapY * 0.5f;
            if(!b->isStatic) b->position.y += overlapY * 0.5f;
        } else {
            if(!a->isStatic) a->position.y += overlapY * 0.5f;
            if(!b->isStatic) b->position.y -= overlapY * 0.5f;
        }
        if(!a->isStatic) a->velocity.y = 0;
        if(!b->isStatic) b->velocity.y = 0;
    }
}
