#ifndef SOLVER_H
#define SOLVER_H
#include "qvector.h"
#include "qpoint.h"
#include "map2d.h"
#include "maze.h"

/**
*Struktura pomocnicza do wyszukiwania i opisu wyniku
*/
struct MapProperties
{
    //lista wierzcholkow, ktore odwiedzily dana kratke w tej samej chwili czasowej
    QList<QPoint> p;
    //lista wierzcholkow potomnych - sluzy do rysowania sciezek
    QList<QPoint> c;
    //obecnie wybrany wezel potomny - index listy c
    int cc;
	//obecnie wybrany wezel przodek - indeks listy p, stosowany podczas powrotu
    int cp;
    //chwila czasowa lub odleglosc od zrodla(brzegu)
    int t;
    //oznacza czy punkt lezy na najkrotszej sciezce miedzy brzegami
    bool isValid;
};

/**
*Klasa Solver rozwiązuje problem znajdowania drogi w labiryncie.
*Dziedziczy z Map2d w celu jednolitego opisu danych i rozwiązania.
*/
class Solver : public Map2d<MapProperties>
{
private:
    Solver();
    int m_currentPath;

public:
    Solver(int width, int height);
	/**
	*Oblicza następną w kolejności ścieżkę.
	*/
    void nextPath();
	/**
	*Zwraca aktualnie wybraną ścieżkę.
	*/
    int getPath(){return m_currentPath;}
    MapProperties getProperties(int x, int y);
    MapProperties getProperties(QPoint point);
	/**
	*Oblicza najkrótsze ścieżki między brzegami mapy.
	*\param maze Mapa z danymi.
	*\param perpendicular Określa czy dozwolony jest ruch prostopadły.
	*\param diagonal Określa czy dozwolony jest ruch na ukos.
	*\param konik Określa czy dozwolony jest ruch podobny do ruchu konia szachowego.
	*/
    int shortestPaths(Maze* maze, bool perpendicular = true, bool diagonal = false, bool konik = false);

};

#endif // SOLVER_H
