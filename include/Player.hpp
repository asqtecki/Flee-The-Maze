#pragma once
#include <raylib.h>
#include "Maze.hpp"
#include "Entity.hpp"

class Player : public Entity {
    Camera3D camera; //fpp mode
    float shift_speed; //booster
    float yaw, pitch; //for rotation, yaw = left right rotation, pitch = up down rotation
    //directions player will move in or face
    Vector3 forward; //forward-backward movement
    Vector3 right; //left-right movement
    public:
        Player(Vector3 spawn);
        Player();
        void Update(const Maze* maze) override;
        Camera3D getCamera() const;
        bool checkCollision(const Maze& maze, Vector3 pos) const override;
};