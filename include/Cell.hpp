//Represent single grid unit in Maze
//Stores position
//Tracks wether a unit has been visited or not, for maze generation

#pragma once

class Cell {
    int rows, columns;
    bool visited;
    bool walls[4]; //0 = top/north, 1 = right/east, 2 = bottom/south, 3 = left/west
    public:
        Cell();
        Cell(int r, int c);
        int getRow() const;
        int getColumn() const;
        bool isVisited() const; //checks if unit has been visited
        void setVisited(bool v); 
        bool hasWall(int idx) const; //checks if a wall exists
        void removeWall(int idx); //removes a certain wall
        void setWall(int idx, bool v); //sets wall state 
};