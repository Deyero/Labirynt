#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "randommapdialog.h"
#include "maze.h"
/**
*Opisuje główne okno aplikacji.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    explicit MainWindow(QWidget *parent = 0);

    private slots:
    void on_actionOtw_rz_triggered();
    void on_actionLosowa_mapa_triggered();
    void on_actionZapisz_triggered();
    void on_actionZezwalaj_na_ruch_prostopad_y_triggered(bool checked);
    void on_actionPoka_siatke_triggered(bool checked);
    void on_actionZezwalaj_na_uko_ne_cie_ki_triggered(bool checked);

    void on_actionKonik_triggered(bool checked);

    void on_actionPoka_wszystkie_triggered(bool checked);

    void on_actionNastepna_triggered();

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
	*Zwraca mapę opisaną w podanym pliku.
	*\param fileName nazwa pliku z danymi.
	*/
    Maze* loadFile(QString fileName);
	/**
	*Zapisuje mapę zawartą w m_maze do pliku.
	*\param fileName nazwa pliku.
	*/
    bool saveFile(QString fileName);
	/**
	*Uaktualnia obiekt składowy klasy Labirynt.
	*Wywoływane przy wczytaniu pliku lub stworzeniu nowego rozwiązania.
	*/
    void updateView(Maze* maze);
	/**
	*Opisuje elementy graficzne okna.
	*/
    Ui::MainWindow ui;
    RandomMapDialog m_rmdialog;
    bool m_allowDiagonal;
    bool m_allowPerpendicular;
    bool m_allowKonik; // :))
};



#endif // MAINWINDOW_H
