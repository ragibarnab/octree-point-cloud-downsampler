#include "point.hpp"

// data structure holding the boundary constraints of a 3-D box 

#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

template<typename T>
class Boundary
{
    // center = a point where the center of the boundary is located
    // length = from center to x coord of boundary edge
    // width = from center to y coord of boundary edge
    // height = from center to z coord of boundary edge
    public:
        Point<T> center;
        T length;
        T width;
        T height;
        Boundary(T x, T y, T z, T l, T w, T h);
        Boundary();
        bool contains(Point<T> p);
};

#endif