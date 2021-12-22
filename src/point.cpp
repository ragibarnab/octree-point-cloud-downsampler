#include <iostream>
#include "point.hpp"

template<typename T>
Point<T>::Point(T x, T y, T z) 
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template<typename T>
Point<T>::Point() 
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p)
{
    os << "x: " << p.x << "\ty: " << p.y << "\tz: " << p.z;
    return os;
}


template class Point<float>;