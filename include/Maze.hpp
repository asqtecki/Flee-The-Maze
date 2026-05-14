#pragma once

#include <vector>
#include "Cell.hpp"
#include "Stack.hpp"
#include <utility>
#include <cstdlib>
#include <raylib.h>

class Maze {
    int rows, columns; //height and width respectively
    int entryRow, entryColumn; //entrance coordinates
    int exitRow, exitColumn; //exit coordinates
    float cellSize = 2.0f; //size of each cell
    std::pair<int, int> Entrance;
    std::pair<int, int> Exit;
    std::vector<std::vector<Cell>> maze; //accumulates cells to form a maze
    const int dirR[4] = {-1, 0, 1, 0}; //row direction for north, east, south, west
    const int dirC[4] = {0, 1, 0, -1}; //column direction for north, east, south, west
    int getOppositeWall(int dir) const; //returns the opposite wall index
    public:
        Maze(int r, int c);
        void generateMaze(); //generates a maze using DFS
        Cell& getCell(int r, int c); //returns a reference to a cell at (r, c)
        const Cell& getCell(int r, int c) const; //returns a const reference to a cell at (r, c)
        void Draw3D(Model& wallM) const; //for raylib drawing
        int getRow() const;
        int getColumn() const;
        float getCellSize() const;
        std::pair<int, int> getEntrance() const;
        std::pair<int, int> getExit() const;
        std::pair<int, int> worldToCell(Vector3 pos) const;
        bool isValid(int r, int c) const; //checks if a cell is within bounds
        bool isWall(int r, int c) const;
};