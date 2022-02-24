#include "point.hpp"
#include "boundary.hpp"
#include "octree.hpp"
#include <memory>


template<typename T>
Octree<T>::Octree(Boundary<T> boundary)
{
    this->boundary = boundary;
    for (int i = 0; i < 8; i++)
        this->children[i] = nullptr;
}


// divides the current octree's boundary into octants, 
// initializes children octrees with appropriate boundary values

template<typename T>
void Octree<T>::subdivide()
{
    Boundary<T> temp = Boundary<T>();
    temp.length = this->boundary.length/2;
    temp.width = this-> boundary.width/2;
    temp.height = this->boundary.height/2;

    // based on a truth table for octants depending on variable signs
    for (int i = 0; i < 8; i++)
    {
        if (i & 0x01)
            temp.center.x = this->boundary.center.x - temp.length;
        else
            temp.center.x = this->boundary.center.x + temp.length;
        if ((i & 0x02) >> 1)
            temp.center.y = this->boundary.center.y - temp.width;
        else
            temp.center.y = this->boundary.center.y + temp.width;
        if ((i & 0x04) >> 2)
            temp.center.z = this->boundary.center.z - temp.height;
        else
            temp.center.z = this->boundary.center.z + temp.height;
        
        this->children[i] = std::make_shared<Octree<T>>(temp);
    }

    this->divided = true;
}

        
// recursive insertion method
template<typename T>
bool Octree<T>::insert(Point<T> p)
{
    if (!this->boundary.contains(p))
        return false;
    if (points.size() < this->capacity)
    {
        points.push_back(p);
        return true;
    }
    else
    {
        if (!divided) 
            this->subdivide();

        for (int i = 0; i < 8; i++)
        {
            bool inserted = this->children[i]->insert(p);
            if (inserted)
                return true;
        }

    }
    return false;
}

template class Octree<float>;