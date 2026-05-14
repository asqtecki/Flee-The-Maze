#include "../include/Cell.hpp"
#include <stdexcept>

Cell::Cell() : rows(0), columns(0), visited(false) {
    for (int i=0;i<4;i++) walls[i] = true;
}

Cell::Cell(int r, int c) : rows(r), columns(c), visited(false) {
    for (int i=0;i<4;i++) walls[i] = true;
}

int Cell::getRow() const {
    return rows;
}

int Cell::getColumn() const {
    return columns;
}

bool Cell::isVisited() const {
    return visited;
}

void Cell::setVisited(bool v) {
    visited = v;
}

bool Cell::hasWall(int idx) const {
    if (idx>=0 && idx<4) return walls[idx];
    throw std::out_of_range("Index out of bounds!");
}

void Cell::removeWall(int idx) {
    if (idx>=0 && idx<4) {
        walls[idx] = false; 
        return;
    }
    throw std::out_of_range("Index out of bounds!");
}

void Cell::setWall(int idx, bool v) {
    if (idx>=0 && idx<4) {
        walls[idx] = v;
        return;
    }
    throw std::out_of_range("Index out of bounds!");
}