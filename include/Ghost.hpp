#pragma once

#include "Entity.hpp"
#include "Maze.hpp"
#include <vector>
#include <utility>

class Ghost : public Entity {
    std::vector<std::pair<int, int>> path; //cell coords
    std::pair<int, int> target; //current player cell
    Vector3 targetPos; //current player pos coords
    float repathTime, repathDelay;
    std::vector<std::pair<int, int>> aStar(
        const Maze& maze,
        std::pair<int, int> start,
        std::pair<int, int> end
    ); //pathfinding
    float manhattan(std::pair<int, int> a, std::pair<int, int> b) const;
    void move(const Maze* maze, Vector3 pp);
    public:
        Ghost(Vector3 spawn);
        Ghost(); //position can be set through inherited setPos func
        void setTarget(std::pair<int, int> tar, Vector3 pos);
        void Update(const Maze* maze) override;
        bool checkCollision(const Maze& maze, Vector3 pos) const override;
        bool isCaught(Vector3 tarPos) const;
        void Draw(Texture2D mod, Camera3D cam) const;
        void setRepathDelay(float rd);
};