#include "../include/Ghost.hpp"
#include <cmath>
#include <algorithm>
#include <map>

Ghost::Ghost() : Entity({0, 1, 0}) , target({0, 0}), repathTime(0.0f),
                repathDelay(0.8f) { speed = 2.0f; }

Ghost::Ghost(Vector3 spawn) : Entity(spawn), target({0, 0}), repathTime(0.0f),
                                repathDelay(0.8f) { speed = 2.0f; }

void Ghost::setTarget(std::pair<int, int> tar, Vector3 pos) { 
    target = tar; 
    targetPos = pos;
}

bool Ghost::checkCollision(const Maze& maze, Vector3 pos) const {
    float cs = maze.getCellSize();
    int r = (int)(pos.z / cs);
    int c = (int)(pos.x / cs);
    if (!maze.isValid(r, c)) return true;
    int cr = (int)(position.z / cs);
    int cc = (int)(position.x / cs);
    if (!maze.isValid(cr, cc)) return true;
    int dr = r - cr;
    int dc = c - cc;
    const Cell& ccell = maze.getCell(cr, cc);
    if (dr==1 && dc==0) return ccell.hasWall(2);
    if (dr==-1 && dc==0) return ccell.hasWall(0);
    if (dr==0 && dc==1) return ccell.hasWall(1);
    if (dr==0 && dc==-1) return ccell.hasWall(3);
    return false;
}

bool Ghost::isCaught(Vector3 tarPos) const {
    float x = position.x - tarPos.x;
    float z = position.z - tarPos.z;
    float s = sqrtf(x*x + z*z);
    return s < 0.5f;
}

float Ghost::manhattan(std::pair<int, int> a, std::pair<int, int> b) const {
    return (float)(abs(a.first-b.first) + abs(a.second-b.second));
}

std::vector<std::pair<int, int>> Ghost::aStar(
        const Maze& maze,
        std::pair<int, int> start,
        std::pair<int, int> end
) {
    std::map<std::pair<int, int>, bool> inOpen, inClosed;
    std::vector<std::pair<int, int>> open;
    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    std::map<std::pair<int, int>, float> gScore;
    open.push_back(start);
    inOpen[start] = true;
    gScore[start] = 0.0f;
    std::vector<std::pair<int, int>> dir = {
        {1, 0}, {-1, 0},
        {0, 1}, {0, -1}
    };
    while (!open.empty()) {
        int bestIdx = 0;
        float bestF = gScore[open[0]] + manhattan(open[0], end);
        for (size_t i=1; i<open.size();i++) {
            float f = gScore[open[i]] + manhattan(open[i], end);
            if (f<bestF) { 
                bestF = f; 
                bestIdx = (int)i; 
            }
        }
        auto curr = open[bestIdx];
        open.erase(open.begin() + bestIdx);
        if (curr==end) {
            std::vector<std::pair<int, int>> res;
            auto step = end;
            while (parent.count(step)) {
                res.push_back(step);
                step = parent[step];
            }
            std::reverse(res.begin(), res.end());
            return res;
        }
        inClosed[curr] = true;
        for (auto& x : dir) {
            int r = curr.first + x.first;
            int c = curr.second + x.second;
            std::pair<int, int> next = {r, c};
            if (!maze.isValid(r, c)) continue;
            if (inClosed.count(next)) continue;
            float cs = maze.getCellSize();
            Vector3 np = {
                c * cs + cs/2.0f,
                position.y,
                r * cs + cs/2.0f
            };
            if (checkCollision(maze, np)) continue;
            float newG = gScore[curr] + 1.0f;
            if (!gScore.count(next) || newG<gScore[next]) {
                gScore[next] = newG;
                parent[next] = curr;
                if (!inOpen.count(next)) {
                    open.push_back(next);
                    inOpen[next] = true;
                }
            }
        }
    }
    return {};
}

void Ghost::move(const Maze* maze, Vector3 pp) {
    float cs = maze->getCellSize();
    Vector3 tar;
    if (path.empty()) tar = {pp.x, pp.y, pp.z};
    else {
        auto next = path.front();
        tar = {
            next.second * cs + cs/2.0f,
            position.y,
            next.first * cs + cs/2.0f
        };
    }
    Vector3 dir = {
        tar.x - position.x,
        0.0f,
        tar.z - position.z
    };
    float s = sqrtf(dir.x * dir.x + dir.z * dir.z);
    if (s>0.05f) {
        dir.x /= s;
        dir.z /= s; 
        position.x += dir.x * speed * GetFrameTime();
        position.z += dir.z * speed * GetFrameTime();
    }
    if (!path.empty()) {
        float s2 = sqrtf((
            position.x - tar.x) * (position.x - tar.x) + 
            (position.z - tar.z) * (position.z - tar.z)
        );
        if (s2<0.2f) path.erase(path.begin());
    }
}

void Ghost::Update(const Maze* maze) {
    repathTime += GetFrameTime();
    auto curr = maze->worldToCell(position);
    if (path.empty() || repathTime>=repathDelay) {
        path = aStar(*maze, curr, target);
        repathTime = 0.0f;
    }
    move(maze, targetPos);
}

void Ghost::Draw(Texture2D mod, Camera3D cam) const {
    DrawBillboard(cam, mod, position, 1.5f, WHITE);
}

void Ghost::setRepathDelay(float rd) { repathDelay = rd; }