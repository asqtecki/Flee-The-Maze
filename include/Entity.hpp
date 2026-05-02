#pragma once

#include <raylib.h>
#include "Maze.hpp"

class Entity {
    protected:
        Vector3 position;
        float speed;
    public:
        Entity(Vector3 spawn = {0, 0, 0}) : position(spawn), speed(0.4f) {}
        virtual void Update(const Maze* maze) = 0;
        Vector3 getPosition() const { return position; }
        void setPosition(Vector3 pos) { position = pos; }
        virtual bool checkCollision(const Maze& maze, Vector3 pos) const = 0;
        virtual ~Entity() {}
};