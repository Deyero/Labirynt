#ifndef GENERATOR_H
#define GENERATOR_H
#include "maze.h"

/**
*Klasa Generator tworzy losową mapę zbudowaną z 0 i 1, co odpowiada wolnemu polu i ścianie w problemie labiryntu.
*/
class Generator
{
    protected:
	/**
	*Generuje liczby losowe wykorzystywane przez generator.
	*/
    static std::minstd_rand rng;

    public:
	/**
	*Wykorzystywana podczas interakcji z użytkownikiem do oznaczenia wybranej metody.
	*/
    enum Method {PLAIN, WALKER};
	/**
	*Dla każdego pola mapy  o szerokości width i wysokości height losuje liczbę 0 albo 1.
	*\param width Szerokość mapy.
	*\param height Wysokość mapy.
	*\param n Liczba kroków.
	*\param p Określa prawdopodobieństwo wylosowania 1.
	*/
    static Maze* plainRandom(int width, int height, double p);
	/**
	*Wybiera losowy punkt na mapie, a następnie podąża w losowym kierunku wykonując n kroków.
	\param width Szerokośc mapy.
	\param height Wysokość mapy.
	*\param wrap Określa czy algorytm może przechodzić przez krawędzie mapy.
	*/
    static Maze* randomWalker(int width, int height, long long n, bool wrap = 1);
};


#endif // GENERATOR_H
