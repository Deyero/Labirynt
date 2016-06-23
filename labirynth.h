#ifndef LABIRYNTH_H
#define LABIRYNTH_H

#include <QWidget>
#include "maze.h"
#include "qvector.h"
#include "qpoint.h"
#include <QList>
#include "solver.h"
#include <QPixmap>
/**
*Klasa Labirynth zajmuje się graficzną reprezentacją problemu labiryntu.
*/
class Labirynth : public QWidget
{
    Q_OBJECT
public:
	/**
	*Inicjalizuje widget.
	*/
    explicit Labirynth(QWidget *parent = 0);
	/**
	*Ustawia mapę do wyświetlania.
	*/
    void setMaze(Maze* maze);
	/**
	*Ustawia mapę zawierającą rozwiązanie problemu.
	*/
    void setSolver(Solver* solver);
	/**
	*Określa czy pokazywać na ekranie wszystkie ścieżki.
	*/
    void showAll(bool show = true);
    /**
	*Okreśa czy pokazywać na ekranie siatkę.
	*/
	void showGrid(bool show = true);

    private:
	/**
	*Zawiera opis mapy.
	*/
    Maze* m_maze;
    /**
	*Zawiera opis rozwiązania.
	*/
	Solver* m_solver;
	/**
	*Okreśa czy pokazywać na ekranie siatkę.
	*/
	bool m_showGrid;
	/**
	*Określa czy pokazywać na ekranie wszystkie ścieżki.
	*/
    bool m_showAll;
	/**
	*Zawiera graficzną reprezentację mapy.
	*/
    QPixmap m_mazePic;
	/**
	Zawiera graficzną reprezentację siatki.
	*/
	QPixmap m_gridPic;
	/**
	*Opisuje szerokość pojedynczej kratki przy tworzeniu graficznej reprezentacji.
	*/
    const int TILEW;
	/**
	*Opisuje wysokość pojedynczej kratki przy tworzeniu graficznej reprezentacji.
	*/
    const int TILEH;
	/**
	*Tworzy graficzną reprezentację siatki.
	*/
    void createPicGrid();
	/**
	*Tworzy graficzną reprezentację mapy.
	*/
    void createPicMaze();
	/**
	*Odświeża okienko z reprezentacją graficzną.
	*/
    void paintEvent(QPaintEvent* event);
};

#endif // LABIRYNTH_H
