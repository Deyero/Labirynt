#include "labirynth.h"
#include <QPainter>
#include <QVector>
#include <QList>
#include <QQueue>




Labirynth::Labirynth(QWidget *parent) :
    QWidget(parent),
    m_maze(nullptr),
    m_solver(nullptr),
    TILEW(32),
    TILEH(32)
{
}

void Labirynth::createPicGrid()
{
    int mapw = m_maze->getWidth();
    int maph = m_maze->getHeight();
    int w = 800;
    int h = 600;
    double tileW = (double)w / mapw;
    double tileH = (double)h / maph;
    m_gridPic = QPixmap(w, h);
    m_gridPic.fill(Qt::transparent);
    QPainter painter(&m_gridPic);
    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidthF(qMin(2.0, 1.0/32.0*tileW));
    painter.setPen(pen);
    for(int i = 0; i < m_maze->getWidth(); ++i)
        painter.drawLine(QPointF(i* tileW, 0), QPointF(i*tileW, h));
    pen.setWidthF(qMin(2.0, 1.0/32.0*tileH));
    painter.setPen(pen);
    for(int i = 0; i < m_maze->getHeight(); ++i)
        painter.drawLine(QPointF(0, i*tileH), QPointF(w, i*tileH));
}

void Labirynth::createPicMaze()
{
    int mapw = m_maze->getWidth();
    int maph = m_maze->getHeight();
    int w = 800;
    int h = 600;
    double tileW = (double)w / mapw;
    double tileH = (double)h / maph;
    m_mazePic = QPixmap(w, h);
    m_mazePic.fill(Qt::white);
    QPainter painter(&m_mazePic);
    painter.setBrush(Qt::black);
    for(int y = 0; y < m_maze->getHeight(); ++y)
    {
        for(int x = 0; x < m_maze->getWidth(); ++x)
        {
            if(m_maze->isWall(x, y))
                painter.drawRect(QRectF(x * tileW, y * tileH, tileW, tileH));
        }
    }

}

void Labirynth::showGrid(bool show)
{
    m_showGrid = show;
}

void Labirynth::setMaze(Maze* maze)
{
    m_maze = maze;
    createPicGrid();
    createPicMaze();
}

void Labirynth::setSolver(Solver* solver)
{
    m_solver = solver;
}

void Labirynth::showAll(bool show)
{
    m_showAll = show;
}

void Labirynth::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(QRectF(0, 0, width(), height()));
    if(m_maze != nullptr)
    {
        //mapa
        double tileW = double(width()) / m_maze->getWidth();
        double tileH = double(height()) / m_maze->getHeight();
        painter.scale(width()/800.0, height()/600.0);
        painter.drawPixmap(0, 0, m_mazePic);
        painter.scale(800.0/width(), 600.0/height());
        painter.setBrush(Qt::NoBrush);

        //ścieżki
        QPen pen;
        pen.setColor(Qt::red);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setWidthF(qMin(tileW, tileH) * 0.2);
        painter.setPen(pen);
        if(m_solver != nullptr)
        {
            if(m_showAll)
            {
                for(int y = 0; y < m_maze->getHeight(); ++y)
                    for(int x = 0; x < m_maze->getWidth(); ++x)
                    {
                        if(m_solver->at(x, y).isValid)
                        {
                            QList<QPoint> p = m_solver->getProperties(x, y).p;
                            for(int i = 0; i < p.size(); ++i)
                                painter.drawLine(QPointF((x + 0.5) * tileW,
                                                         (y + 0.5) * tileH),
                                                 QPointF((p[i].x() + 0.5) * tileW,
                                                         (p[i].y() + 0.5) * tileH));
                        }
                    }
            }
            else
            {
                QPoint tile(m_solver->getPath(), 0);
                if(tile != QPoint(-1, 0))
                    while(tile.y() < m_solver->getHeight() - 1)
                    {
                        QPoint next = m_solver->at(tile).c[m_solver->at(tile).cc];
                        painter.drawLine(QPointF((tile.x() + 0.5) * tileW,
                                                 (tile.y() + 0.5) * tileH),
                                         QPointF((next.x() + 0.5) * tileW,
                                                 (next.y() + 0.5) * tileH));
                        tile = next;
                    }
            }
        }

        //siatka
        if(m_showGrid)
        {
            pen.setColor(Qt::gray);
            pen.setWidthF(qMin(2.0, 1.0/32.0*tileW));
            painter.setPen(pen);
            painter.setBrush(Qt::gray);
            for(int i = 0; i < m_maze->getWidth(); ++i)
                painter.drawLine(QPointF(i* tileW, 0), QPointF(i*tileW, height()));
            pen.setWidthF(qMin(2.0, 1.0/32.0*tileH));
            painter.setPen(pen);
            for(int i = 0; i < m_maze->getHeight(); ++i)
                painter.drawLine(QPointF(0, i*tileH), QPointF(width(), i*tileH));
//            painter.scale(width()/800.0, height()/600.0);
//            painter.drawPixmap(0, 0, m_gridPic);

        }
    }
}
