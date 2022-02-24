#include <vector>
#include <memory>
// octree implementation 

#ifndef OCTREE_HPP
#define OCTREE_HPP

template<typename T>
class Octree
{
    public:
        int capacity = 1;          // capacity: parameter to tune
        bool divided = false;
        Boundary<T> boundary;
        std::vector<Point<T>> points;
        std::shared_ptr<Octree<T>> children[8];

        Octree(Boundary<T> boundary);
        // divides the current octree's boundary into octants, 
        // initializes children octrees with appropriate boundary values
        void subdivide();
        
        // recursive insertion method
        bool insert(Point<T> p);
};

#endif