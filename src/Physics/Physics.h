#pragma once
#include <vector>
#include <cmath>
#include <algorithm>

// Forward declaration
class Level;

struct Vector2D {
    float x, y;

    Vector2D(float _x = 0, float _y = 0) : x(_x), y(_y) {}

    Vector2D operator+(const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
    Vector2D operator-(const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
    Vector2D operator*(float s) const { return Vector2D(x * s, y * s); }
    
    float Length() const { return std::sqrt(x * x + y * y); }
    Vector2D Normalize() const {
        float l = Length();
        if (l > 0) return Vector2D(x / l, y / l);
        return Vector2D(0, 0);
    }
};

enum ColliderType { AABB, CIRCLE };

struct Collider {
    ColliderType type;
    float width, height;
    Vector2D offset;
};

class RigidBody {
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D force;
    
    float mass;
    float friction;
    bool isStatic;
    bool isGrounded; // For jumping

    Collider collider;

    RigidBody() : mass(1.0f), friction(0.1f), isStatic(false), isGrounded(false) {}

    void ApplyForce(Vector2D f) {
        force = force + f;
    }

    void Update(float dt) {
        if (isStatic) return;

        acceleration = force * (1.0f / mass);
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        velocity = velocity * (1.0f - friction * dt);
        force = Vector2D(0, 0);
    }
};

class PhysicsWorld {
public:
    void SetLevel(Level* level) { m_Level = level; }
    void AddBody(RigidBody* body);
    void RemoveBody(RigidBody* body);
    void Update(float dt);

private:
    std::vector<RigidBody*> m_Bodies;
    Level* m_Level = nullptr;
    
    bool CheckCollision(RigidBody* a, RigidBody* b);
    void ResolveCollision(RigidBody* a, RigidBody* b);
    void ResolveMapCollision(RigidBody* body);
};
