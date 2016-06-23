#ifndef MAZE_H
#define MAZE_H

#include "qpoint.h"
#include "map2d.h"

/**
*Opisuje mapę o wartościach 0-1
*0 oznacza wolne pole,
*1 oznacza ścianę.
*Dziedziczy z Map2d w celu skrócenia nazwy, oraz korzystania z bardziej opisowych funkcji.
*/
class Maze : public Map2d<bool>
{
    public:
	/**
	*Tworzy pustą mapę.
	*/
    Maze();
	/**
	*Tworzy mapę o szerokości width i wysokości height.
	*/
    Maze(int width, int height);
	/**
	*Zwraca true jeśli w punkcie (x,y) znajduje się ściana.
	*/
    bool isWall(int x, int y);
	/**
	*Zwraca true jeśli w punkcie opisanym przez point znajduje się ściana.
	*/
    bool isWall(QPoint point);
};
#endif // MAZE_H
