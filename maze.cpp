#include "maze.h"
#include "qpoint.h"


Maze::Maze():
    Map2d<bool>()
{

}

Maze::Maze(int width, int height):
    Map2d<bool>(width, height)
{

}

bool Maze::isWall(int x, int y)
{
    if(this->at(x, y))
        return true;
    return false;
}

bool Maze::isWall(QPoint point)
{
    if(this->at(point))
        return true;
    return false;
}
