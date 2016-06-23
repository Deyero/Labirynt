#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include "solver.h"
#include "generator.h"
#include <QException>
#include <exception>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_maze(nullptr),
    m_solver(nullptr),
    m_rmdialog(this)
{
    ui.setupUi(this);
    ui.labirynth->showGrid(ui.actionPoka_siatke->isChecked());
    ui.labirynth->showAll(ui.actionPoka_siatke->isChecked());
    m_allowDiagonal = ui.actionZezwalaj_na_uko_ne_cie_ki->isChecked();
    m_allowPerpendicular = ui.actionZezwalaj_na_ruch_prostopad_y->isChecked();
    m_allowKonik = ui.actionKonik->isChecked();
}

void MainWindow::on_actionOtw_rz_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Otworz");
    Maze* maze = loadFile(fileName);
    updateView(maze);
}

Maze* MainWindow::loadFile(QString fileName)
{
    Maze* maze = nullptr;
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Błąd", "Nie udało się otworzyć pliku.");
            return maze;
        }
        QTextStream in(&file);
        int width, height;
        in>>height;
        if(in.status())
        {
            QMessageBox::critical(this, "Błąd", "Błędny format pliku.");
            return maze;
        }
        in>>width;
        if(in.status())
        {
            QMessageBox::critical(this, "Błąd", "Błędny format plku.");
            return maze;
        }
        maze = new Maze;
        maze->setSize(width, height);
        for(int y = 0; y < height; ++y)
        {
            QString line;
            in>>line;
            if(line.length() != width)
            {
                QMessageBox::critical(this, "Błąd", "Błędny format pliku.");
                delete maze;
                maze = nullptr;
                break;
            }
            for(int x = 0; x < width; ++x)
            {
                bool toAdd = 0;
                switch(line[x].toLatin1())
                {
                    case 'C': toAdd = 1; break;
                    case 'B': toAdd = 0; break;
                    default:
                    QMessageBox::critical(this, "Błąd", "Błędny format pliku.");
                    delete maze;
                    return nullptr;
                }
                maze->at(x, y) = toAdd;
            }
        }
        file.close();
    }
    return maze;
}

void MainWindow::updateView(Maze* maze)
{
    if(maze != nullptr)
    {
        int splength;
        Solver* solver = nullptr;
        try
        {
            solver = new Solver(maze->getWidth(), maze->getHeight());
            splength = solver->shortestPaths(maze, m_allowPerpendicular, m_allowDiagonal, m_allowKonik);
            ui.labirynth->setMaze(maze);
            ui.labirynth->setSolver(solver);
            if(m_maze != nullptr && maze != m_maze)
                delete m_maze;
            m_maze = maze;
            if(m_solver != nullptr)
                delete m_solver;
            m_solver = solver;
            ui.labirynth->update();

            QString str = "Labirynt";
            if(splength < INT_MAX)
                str += ", dlugosc = " + QString::number(splength);
            else
                str +=", droga nie istnieje";
            this->setWindowTitle(str);

        }
        catch(std::exception &e)
        {
            QMessageBox::critical(this, "Błąd", e.what());
            if(solver != nullptr)
                delete solver;
            if(maze != nullptr && maze != m_maze)
                delete maze;
        }
    }
}

void MainWindow::on_actionLosowa_mapa_triggered()
{
    if(m_rmdialog.exec())
    {
        try
        {
            bool ok = true;
            Maze* maze = nullptr;

            int width = m_rmdialog.getWidth().toInt(&ok);
            if(!ok)
                throw "Szerokość musi być liczbą całkowitą";
            if(width <= 0)
                throw "Szerokość musi być większa od zera";

            int height = m_rmdialog.getHeight().toInt(&ok);
            if(!ok)
                throw "Wysokość musi być liczbą całkowitą";
            if(height <= 0)
                throw "Wysokość musi być większa od zera";

            Generator::Method method = m_rmdialog.getMethod();
            if(method == Generator::PLAIN)
            {
                double p = m_rmdialog.getParam1().toDouble(&ok);
                if(!ok)
                    throw "Niepoprawna wartość parametru p";
                if(p < 0 || p > 1)
                    throw "P musi być z zakresu [0; 1]";
                maze = Generator::plainRandom(width, height, p);
            }
            if(method == Generator::WALKER)
            {
                long long n = m_rmdialog.getParam1().toLongLong(&ok);
                if(!ok)
                    throw "Niepoprawna wartość parametru n";
                if(n <= 0)
                    throw "Ilośc kroków musi być większa od zera";
                maze = Generator::randomWalker(width, height, n);
            }

        updateView(maze);
        }
        catch(const char *str)
        {
            QMessageBox::critical(this, "Błąd", str);
        }
    }

}

void MainWindow::on_actionZapisz_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz...");
    if(!fileName.isEmpty())
        if(!saveFile(fileName))
           QMessageBox::critical(this, "Błąd", "Wystąpił błąd podczas zapisu pliku");
}

bool MainWindow::saveFile(QString fileName)
{
    if(m_maze != nullptr)
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
            return 0;
        QTextStream out(&file);
        int height = m_maze->getHeight();
        int width = m_maze->getWidth();
        out<<height<<" "<<width<<"\n";
        for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
                out<< (m_maze->isWall(x, y) ? 'C' : 'B');
            out<<"\n";
        }
        file.close();
        return 1;
    }
    return 0;
}



void MainWindow::on_actionZezwalaj_na_ruch_prostopad_y_triggered(bool checked)
{
    this->m_allowPerpendicular = checked;
    updateView(m_maze);
}

void MainWindow::on_actionPoka_siatke_triggered(bool checked)
{
    ui.labirynth->showGrid(checked);
    ui.labirynth->update();
}

void MainWindow::on_actionZezwalaj_na_uko_ne_cie_ki_triggered(bool checked)
{
    this->m_allowDiagonal = checked;
    updateView(m_maze);

}

void MainWindow::on_actionKonik_triggered(bool checked)
{
    this->m_allowKonik = checked;
    updateView(m_maze);
}

void MainWindow::on_actionPoka_wszystkie_triggered(bool checked)
{
    ui.labirynth->showAll(checked);
    ui.labirynth->update();
    ui.actionNastepna->setEnabled(!checked);
}

void MainWindow::on_actionNastepna_triggered()
{
    m_solver->nextPath();
    ui.labirynth->update();
}
