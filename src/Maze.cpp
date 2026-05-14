#include "../include/Maze.hpp"
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <raylib.h>
#include <cmath>
#include "../include/Stack.hpp"

Maze::Maze(int r, int c) : rows(r), columns(c) {
    maze.resize(rows, std::vector<Cell>(columns));
    for (int i=0;i<rows;i++) {
        for (int j=0;j<columns;j++) maze[i][j] = Cell(i, j);
    }
}

int Maze::getRow() const { return rows; }
int Maze::getColumn() const { return columns; }

bool Maze::isValid(int r, int c) const { return (r>=0 && r<rows && c>=0 && c<columns); } 

int Maze::getOppositeWall(int dir) const {
    if (dir==0) return 2; // north -> south
    if (dir==2) return 0; // south -> north
    if (dir==1) return 3; // east -> west
    if (dir==3) return 1; // west -> east
    throw std::out_of_range("Invalid direction");
}

Cell& Maze::getCell(int r, int c) { return maze[r][c]; }

const Cell& Maze::getCell(int r, int c) const { return maze[r][c]; }

void Maze::generateMaze() {
    Stack<std::pair<int, int>> s;
    int rs = 0, rc = 0; //starting cell
    maze[rs][rc].setVisited(true);
    s.push({rs, rc});
    while (!s.isEmpty()) { //when all cells are visited, stack becomes empty
        auto [r, c] = s.top(); //current coords
        std::vector<std::pair<int, int>> neighbors;
        std::vector<int> direc;
        for (int i=0;i<4;i++) {
            //neighbor coords in direction i = {0, 1, 2, 3} = {N, E, S, W}
            int nr = r + dirR[i];
            int nc = c + dirC[i];
            if (isValid(nr, nc) && !maze[nr][nc].isVisited()) {
                neighbors.push_back({nr, nc});
                direc.push_back(i);
            }
        }
        if (!neighbors.empty()) {
            int idx = std::rand() % neighbors.size();
            int nr = neighbors[idx].first;
            int nc = neighbors[idx].second;
            int dir = direc[idx];
            if (dir<0 || dir>3) throw std::out_of_range("Invalid direction in maze!");
            maze[r][c].removeWall(dir);
            maze[nr][nc].removeWall(getOppositeWall(dir));
            maze[nr][nc].setVisited(true);
            s.push({nr, nc});
        }
        else s.pop();
    }
    int entry = std::rand() % 4;
    int exit;
    do {
        exit = std::rand() % 4;
    } while (exit == entry);
    if (entry==0) {
        entryRow = 0;
        entryColumn = std::rand() % columns;
        Entrance = {entryRow, entryColumn};
        maze[entryRow][entryColumn].removeWall(0);
    }
    else if (entry==1) {
        entryRow = std::rand() % rows;
        entryColumn = columns - 1; //right index = total col - 1
        Entrance = {entryRow, entryColumn};
        maze[entryRow][entryColumn].removeWall(1);
    }
    else if (entry==2) {
        entryRow = rows - 1; //bottom index = total row - 1
        entryColumn = std::rand() % columns;
        Entrance = {entryRow, entryColumn};
        maze[entryRow][entryColumn].removeWall(2);
    }
    else {
        entryRow = std::rand() % rows;
        entryColumn = 0;
        Entrance = {entryRow, entryColumn};
        maze[entryRow][entryColumn].removeWall(3);
    }
    if (exit==0) {
        exitRow = 0;
        exitColumn = std::rand() % columns;
        Exit = {exitRow, exitColumn};
        maze[exitRow][exitColumn].removeWall(0);
    }
    else if (exit==1) {
        exitRow = std::rand() % rows;
        exitColumn = columns - 1;
        Exit = {exitRow, exitColumn};
        maze[exitRow][exitColumn].removeWall(1);
    }
    else if (exit==2) {
        exitRow = rows - 1;
        exitColumn = std::rand() % columns;
        Exit = {exitRow, exitColumn};
        maze[exitRow][exitColumn].removeWall(2);
    }
    else {
        exitRow = std::rand() % rows;
        exitColumn = 0;
        Exit = {exitRow, exitColumn};
        maze[exitRow][exitColumn].removeWall(3);
    }
}

float Maze::getCellSize() const { return cellSize; }

void Maze::Draw3D(Model& wallM) const {
    float wallHeight = 2.0f;
    float wallThickness = 0.1f;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<columns;j++) {
            float x = j * cellSize;
            float z = i * cellSize;
            if (maze[i][j].hasWall(0)) {
                    DrawModelEx(
                        wallM,
                        {x+cellSize/2, wallHeight/2, z},
                        {0.0f, 1.0f, 0.0f},
                        0.0f,
                        {cellSize, wallHeight, wallThickness},
                        WHITE
                    );
            }
            if (maze[i][j].hasWall(1)) {
                DrawModelEx(
                    wallM,
                    {x+cellSize, wallHeight/2, z+cellSize/2},
                    {0.0f, 1.0f, 0.0f},
                    0.0f,
                    {wallThickness, wallHeight, cellSize},
                    WHITE
                );
            }
            if (maze[i][j].hasWall(2)) {
                DrawModelEx(
                    wallM,
                    {x+cellSize/2, wallHeight/2, z+cellSize},
                    {0.0f, 1.0f, 0.0f},
                    0.0f,                    
                    {cellSize, wallHeight, wallThickness}, WHITE
                );
            }
            if (maze[i][j].hasWall(3)) {
                DrawModelEx(
                    wallM,
                    {x, wallHeight/2, z+cellSize/2},
                    {0.0f, 1.0f, 0.0f},
                    0.0f,
                    {wallThickness, wallHeight, cellSize},
                    WHITE
                );
            }
        }
    }
}

std::pair<int, int> Maze::getEntrance() const { return Entrance; }
std::pair<int, int> Maze::getExit() const { return Exit; }

std::pair<int, int> Maze::worldToCell(Vector3 pos) const {
    int col = std::max(0, static_cast<int>(pos.x/cellSize));
    int row = std::max(0, static_cast<int>(pos.z/cellSize));
    return {row, col};
}