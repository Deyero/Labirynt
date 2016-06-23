#include "generator.h"
#include <random>

std::minstd_rand Generator::rng;

Maze* Generator::plainRandom(int width, int height, double p)
{
    Maze* maze = new Maze(width, height);
    std::uniform_real_distribution<> ranF;
    for(int i = 0, size = maze->getSize(); i < size; ++i)
    {
        if(ranF(rng) <= p)
            maze->at(i) = 1;
        else
            maze->at(i) = 0;
    }


    return maze;
}

Maze* Generator::randomWalker(int width, int height, long long n, bool wrap)
{
    Maze* maze = new Maze(width, height);
    for(int y = 0; y < height; ++y)
        for(int x = 0; x < width; ++x)
            maze->at(x, y) = 1;
    QPoint pos = QPoint(rng() %  width, rng() % height);
    std::uniform_int_distribution<> ran(0, 3);
    while(n--)
    {
        maze->at(pos) = 0;
        int d = ran(rng);
        if(wrap)
            switch(d)
            {
                case 0:
                    pos.ry()--;
                    if(pos.ry() < 0)
                        pos.ry() += height;
                    break;
                case 1:
                    pos.rx()++;
                    if(pos.rx() >= width)
                        pos.rx() = 0;
                    break;
                case 2:
                    pos.ry()++;
                    if(pos.ry() >= height)
                        pos.ry() = 0;
                    break;
                case 3:
                    pos.rx()--;
                    if(pos.rx() < 0)
                        pos.rx() += width;
                    break;
            }
    }
    return maze;
}
