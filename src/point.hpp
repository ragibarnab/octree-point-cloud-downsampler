#include <iostream>

#ifndef POINT_HPP
#define POINT_HPP

template<typename T>
class Point
{
    public:
        T x;
        T y;
        T z;
        Point(T x, T y, T z);
        Point();
        template<typename W>
        friend std::ostream& operator<<(std::ostream& os, const Point<W>& p);
};

#endif