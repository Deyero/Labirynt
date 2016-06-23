#ifndef MAP2D_H
#define MAP2D_H

#include "qvector.h"
#include "qpoint.h"
/**
*Klasa Map2d definiuje tablicę, którą można traktować jako mapę adresowalną za pomocą współrzędnych x,y.
*Współrzędne muszą być całkowite i nieujemne.
*Do adresowania wykorzystywana jest klasa QPoint zdefiniowana w qpoint.h.
*/
template<typename T>
class Map2d
{
    public:
	/**
	*Tworzy pustą mapę o zerowych wymiarach.
	*/
    Map2d(): m_width(0), m_height(0), m_size(0){}

	/**
	*Tworzy mapę o szerokości width i wysokości height.
	*/
    Map2d(int width, int height):
        m_width(width),
        m_height(height),
        m_size(width * height),
        m_container(width * height)
    {   }

	/**
	*Zwraca referencję na element znajdujący się na pozycji (x,y)
	*/
    T& at(int x, int y){return m_container[m_width * y + x];}
	/**
	*Zwraca referencję na element wskazany przez point.
	*/
    T& at(QPoint point){return m_container[m_width * point.y() + point.x()];}
	/**
	*Zwraca referencję na element znajdujący się na pozycji index.
	*/
    T& at(int index){return m_container[index];}
	/**
	*Zwraca true jeśli mapa zawiera współrzędne (x,y).
	*/
    bool contains(int x, int y){return x >= 0 && x < m_width && y >= 0 && y < m_height;}
	/**
	*Zwraca true jeśli mapa zawiera współrzędne opisane przez point.
	*/
    bool contains(QPoint point){return point.x() >= 0 && point.x() < m_width && point.y() >= 0 && point.y() < m_height;}
	/**
	*Zwraca wysokośc mapy.
	*/
    int getHeight(){return m_height;}
	/**
	*Zwraca szerokośc mapy.
	*/
    int getWidth(){return m_width;}
	/**
	*Zwraca rozmiar mapy. Wynosi on szerokość * wysokość.
	*/
    int getSize(){return m_size;}
	/**
	*Ustawia rozmiar mapy na szerokośc x i wysokośc y.
	*/
    void setSize(int x, int y)
    {
        m_height = y;
        m_width = x;
        m_size = x * y;
        m_container.resize(m_size);
    }
	
	/**
	*Zwraca liniowy indeks elementu o współrzędnych (x,y).
	*/
    int linear(int x, int y){return y * m_width + x;}
	/**
	*Zwraca liniowy indeks elementu o współrzędnych opisanych przez point.
	*/
    int linear(QPoint point){return point.y() * m_width + point.x();}

    protected:
	/**
	*Szerokośc mapy.
	*/
    int m_width;
	/**
	*Wysokośc mapy.
	*/
    int m_height;
	/**
	*Rozmiar mapy.
	*/
    int m_size;
	/**
	*Właściwa tablica z danymi.
	*/
    QVector<T> m_container;
};

#endif // MAP2D_H
