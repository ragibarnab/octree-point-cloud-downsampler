#include "boundary.hpp"
#include "point.hpp"

// data structure holding the boundary constraints of a 3-D box 

template<typename T>
Boundary<T>::Boundary(T x, T y, T z, T l, T w, T h)
{
    length = l;
    width = w;
    height = h;
    center = Point<T>(x,y,z);
}

template<typename T>
Boundary<T>::Boundary()
{
    length = 0;
    width = 0;
    height = 0;
    center = Point<T>();
}

template<typename T>
bool Boundary<T>::contains(Point<T> p)
{
    bool contain = false;
    if ((p.x <= center.x + length) && (p.x >= center.x - length))
    {
        if ((p.y <= center.y + width) && (p.y >= center.y - width))
        {
            if ((p.z <= center.z + height) && (p.z >= center.z - height))
            {
                contain = true;
            }
        }
    }
    return contain;
}


template class Boundary<float>;

