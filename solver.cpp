#include "solver.h"
#include "maze.h"
#include "qqueue.h"

Solver::Solver():
    Map2d<MapProperties>()
{
}

Solver::Solver(int width, int height):
    Map2d<MapProperties>(width, height)
{

}

void Solver::nextPath()
{
    if(m_currentPath == -1)
        return;
    QPoint tile = QPoint(m_currentPath, 0);
    while(tile.y() < m_height - 1)
    {
        QPoint next(at(tile).c[at(tile).cc]);
        at(next).cp = at(next).p.indexOf(tile);
        tile = next;
    }

    while(true)
    {
        if(at(tile).cc + 1 < at(tile).c.size())
        {
            break;
        }
        else
        {
            at(tile).cc = -1;
            if(!at(tile).p.empty())
                tile = at(tile).p[at(tile).cp];
            else
            {
                int i = m_currentPath;
                while(!at(++i % m_width).isValid);
                i %= m_width;
                m_currentPath = i;
                tile = QPoint(i, 0);
                break;
            }
        }
    }
    while(tile.y() < m_height - 1)
    {
        at(tile).cc++;
        tile = at(tile).c[at(tile).cc];
    }
}

MapProperties Solver::getProperties(int x, int y)
{
    return m_container[y * m_width + x];
}

MapProperties Solver::getProperties(QPoint point)
{
    return m_container[point.y() * m_width + point.x()];
}

int Solver::shortestPaths(Maze* maze, bool perpendicular, bool diagonal, bool konik)
{
    int width = m_width;
    int height = m_height;

    //inicjalizacja
    const int INF = INT_MAX;
    for(int i = width; i < maze->getSize(); ++i)
    {
        m_container[i].p.clear();
        m_container[i].c.clear();
        m_container[i].t = INF;
        m_container[i].isValid = 0;
    }

    //oddzielna inicjalizacja dla y = 0
    QQueue<QPoint> queue;
    for(int x = 0; x < width; ++x)
    {
        if(!maze->isWall(x, 0))
            queue.enqueue(QPoint(x, 0));
        m_container[x].t = 0;
        m_container[x].isValid = 0;
    }

    //dlugosc najkrotszej drogi z gory na sam dol
    int tmin = INF;

    while(!queue.isEmpty())
    {
        QPoint tile = queue.dequeue();
        int t = m_container[maze->linear(tile)].t;

        //szukamy minimalnego czasu w ostatnim wierszu
        if(tile.y() == height - 1 && t < tmin)
            tmin = t;

        QPoint up(tile.x(), tile.y() - 1);
        QPoint right(tile.x() + 1, tile.y());
        QPoint down(tile.x(), tile.y() + 1);
        QPoint left(tile.x() - 1, tile.y());

        QPoint upLeft(tile.x() - 1, tile.y() - 1);
        QPoint upRight(tile.x() + 1, tile.y() - 1);
        QPoint downRight(tile.x() + 1, tile.y() + 1);
        QPoint downLeft(tile.x() - 1, tile.y() + 1);

        QPoint konik1(tile.x() + 1, tile.y() - 2);
        QPoint konik2(tile.x() + 2, tile.y() - 1);
        QPoint konik3(tile.x() + 2, tile.y() + 1);
        QPoint konik4(tile.x() + 1, tile.y() + 2);
        QPoint konik5(tile.x() - 1, tile.y() + 2);
        QPoint konik6(tile.x() - 2, tile.y() + 1);
        QPoint konik7(tile.x() - 2, tile.y() - 1);
        QPoint konik8(tile.x() - 1, tile.y() - 2);

        QPoint neighbours[16] = {up, right, down, left, upLeft, upRight, downRight, downLeft,
                                konik1, konik2, konik3, konik4, konik5, konik6, konik7, konik8};

        for(int i = 0; i < 16; ++i)
        {
            if((i < 4 && perpendicular) || (i >= 4 && i < 8 && diagonal) || (i >= 8 && konik))
            {
                if(contains(neighbours[i]) && !maze->isWall(neighbours[i]) &&
                        at(neighbours[i]).t >= t + 1)
                {
                    if(at(neighbours[i]).t == INF)
                    {
                        at(neighbours[i]).t = t + 1;
                        queue.enqueue(neighbours[i]);
                    }
                    at(neighbours[i]).p.append(tile);
                }
            }
        }
    }

    //szukamy wierzcholkow faktycznie lezacych na najkrotszych sciezkach
    //poprzez przejscie sciezek od dolu do gory
    //rozpoczynamy od ostatniego rzedu
    for(int x = 0, index = maze->linear(0, height - 1); x < width; ++x, ++index)
    {
        if(m_container[index].t == tmin)
        {
            queue.enqueue(QPoint(x, height - 1));
            m_container[index].isValid = true;
//            for(int j = 0; j < m_container[index].p.size(); ++j)
//                //m_container[linear(m_container[index].p[j])].c.append(QPoint(x, height - 1));
//                at(at(x, height - 1).p[j]).c.append(QPoint(x, height-1));
        }
    }

    while(!queue.isEmpty())
    {
        QPoint tile = queue.dequeue();
        int index = this->linear(tile);
        for(int i = 0; i < m_container[index].p.size(); ++i)
        {
            if(!this->at(m_container[index].p[i]).isValid)
            {
                this->at(m_container[index].p[i]).isValid = true;
                queue.enqueue(m_container[index].p[i]);
            }
            at(at(tile).p[i]).c.append(tile);
        }
    }

    for(int i = 0; i < m_size; ++i)
    {
        m_container[i].cc = -1;
        m_container[i].cp = -1;
    }

    //inicjalizacja pierwszej sciezki
    int i = 0;
    while(!m_container[i].isValid && i < m_width)
        ++i;
    if(i < m_width)
    {
        m_currentPath = i;
        QPoint tile = QPoint(i, 0);
        while(tile.y() != m_height - 1)
        {
            at(tile).cc = 0;
            tile = at(tile).c[0];
        }
    }
    else
        m_currentPath = -1;
    return tmin;
}
