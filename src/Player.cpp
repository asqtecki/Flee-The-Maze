#include "../include/Player.hpp"
#include <cmath>



Player::Player(Vector3 spawn) : Entity(spawn), shift_speed(2.5f), yaw(0.0f), pitch(0.0f) {
    speed = 0.03f;
    camera.position = position;
    camera.target = (Vector3){spawn.x, spawn.y, spawn.z + 1.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    forward = {0.0f, 0.0f, 1.0f};
    right = {1.0f, 0.0f, 0.0f};
}

Player::Player(): Entity({0, 0, 0}) {}

bool Player::checkCollision(const Maze& maze, Vector3 pos) const {
    float cells = maze.getCellSize(); //cell size
    int col = (int)(pos.x/cells);
    int row = (int)(pos.z/cells);
    if (row<0 || row>=maze.getRow() || col<0 || col>=maze.getColumn()) return true;
    const Cell& cell = maze.getCell(row, col);
    float ox = fmod(pos.x, cells); //offset X
    float oz = fmod(pos.z, cells); //offset Y
    float ps = 0.2f; //player size
    if (cell.hasWall(0) && oz<ps) return true;
    if (cell.hasWall(1) && ox>(cells-ps)) return true;
    if (cell.hasWall(2) && oz>(cells-ps)) return true;
    if (cell.hasWall(3) && ox<ps) return true;
    return false;
}

void Player::Update(const Maze* maze) {
    float sensitivity = 0.005f;
    Vector2 md = GetMouseDelta();
    yaw -= md.x * sensitivity;
    pitch -= md.y * sensitivity;
    if (pitch>1.5f) pitch = 1.5f;
    if (pitch<-1.5f) pitch = -1.5f;
    Vector3 direc;
    direc.x = cosf(pitch) * sinf(yaw);
    direc.y = sinf(pitch);
    direc.z = cosf(pitch) * cosf(yaw);
    camera.target = {
        camera.position.x + direc.x, 
        camera.position.y + direc.y,
        camera.position.z + direc.z
    };
    forward.x = direc.x;
    forward.y = 0.0f;
    forward.z = direc.z;
    float len = sqrtf(forward.x*forward.x + forward.y*forward.y + forward.z*forward.z);
    if (len!=0) {
        forward.x /= len;
        forward.y /= len;
        forward.z /= len;
    }
    right.x = forward.y * camera.up.z - forward.z * camera.up.y;
    right.y = forward.z * camera.up.x - forward.x * camera.up.z;
    right.z = forward.x * camera.up.y - forward.y * camera.up.x;
    float len2 = sqrtf(right.x*right.x + right.y*right.y + right.z*right.z);
    if (len2!=0) {
        right.x /= len2;
        right.y /= len2;
        right.z /= len2;
    }
    speed = 0.03f;
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) speed *= shift_speed;
    if (IsKeyDown(KEY_W)) {
        Vector3 pos = camera.position;
        pos.x += forward.x * speed;
        pos.z += forward.z * speed;
        if (!checkCollision(*maze, pos)) {
            camera.position = pos;
            position = pos;
        }
    }
    if (IsKeyDown(KEY_S)) {
        Vector3 pos = camera.position;
        pos.x -= forward.x * speed;
        pos.z -= forward.z * speed;
        if (!checkCollision(*maze, pos)) {
            camera.position = pos;
            position = pos;
        }
    }
    if (IsKeyDown(KEY_D)) {
        Vector3 pos = camera.position;
        pos.x += right.x * speed;
        pos.z += right.z * speed;
        if (!checkCollision(*maze, pos)) {
            camera.position = pos;
            position = pos;
        }
    }
    if (IsKeyDown(KEY_A)) {
        Vector3 pos = camera.position;
        pos.x -= right.x * speed;
        pos.z -= right.z * speed;
        if (!checkCollision(*maze, pos)) {
            camera.position = pos;
            position = pos;
        }
    }
}

Camera3D Player::getCamera() const { return camera; }