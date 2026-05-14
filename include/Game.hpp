#pragma once

#include <raylib.h>
#include "Maze.hpp"
#include "Player.hpp"
#include "Ghost.hpp"
#include "Queue.hpp"
#include <vector>

enum GameState {
    PLAYING, //1
    JUMPSCARE, //2
    LOADING, //3
    CLEAR, //4
};

class Game {
    struct Star {
        Vector3 position;
        float size, twinkles; //twinkling intensity
    };
    //sounds and music
    Music permBgSound;
    Sound exit;
    Sound jumpscare;
    bool exitPlayed;

    std::vector<Star> stars;
    Queue<Ghost> ghosts;
    int ghostPerLevel;
    Maze* maze;
    Player player;
    Texture2D grass;
    Texture2D ghost;
    GameState state;
    int mazeSize;
    int level;
    float loadingTimer, loadingDuration;
    Model wallModel;
    Model grassModel;
    float jumpscareTimer, jumpscareDuration;
    bool isAtExit() const;
    public:
        Game(Model wall);
        void Update();
        void Draw();
        ~Game();
};