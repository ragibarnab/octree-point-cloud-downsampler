#include "point.hpp"
#include "boundary.hpp"
#include "octree.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// my short and dirty downsampling technique: recursively collect the stored points of the octree until a certain target depth of the structure
template<typename T>
void downsample(Octree<T>* octree, vector<Point<T>*>& out, int target_depth, int depth=0)
{
    if (!octree)
        return;
    if (depth < target_depth)
    {
        for  (int i = 0; i < 8; i++)
            downsample(octree->children[i], out, target_depth, depth+1);
    }
    out.insert(out.end(), octree->points.begin(), octree->points.end());
}



int main(int argc, char const *argv[])
{
    // center of root boundary at origin, with 10 meters out from center in x,y,z
    Boundary<float> b = Boundary<float>(0,0,0,10.0,10.0,10.0);
    Octree<float>* ot = new Octree<float>(b);

    // inserting points one by one into the tree
    ifstream infil("input.csv");
    if (infil.is_open())
    {
        string temp;
        getline(infil, temp);

        while(getline(infil, temp, ','))
        {
            float x = stof(temp);
            getline(infil, temp, ',');
            float y = stof(temp);
            getline(infil, temp);
            float z = stof(temp);
            Point<float>* p = new Point<float>(x,y,z);
            ot->insert(p);
        }
    }
    infil.close();

    // create a vector to store the downsampled output, prints size of the output
    vector<Point<float>*> downsampled;
    downsample(ot, downsampled, 8);     // depth: parameter to tune                            

    // write output into a file on disk
    ofstream outfile("output.csv");
    if (outfile.is_open())
    {
        char buffer[100] = "x,y,z\n";
        outfile << buffer;
        for (int i = 0; i < downsampled.size(); i++)
        {
            Point<float> p = *downsampled.at(i);
            snprintf(buffer, sizeof(buffer), "%f,%f,%f\n", p.x, p.y, p.z);
            outfile << buffer;
        }
    }
    outfile.close();
    return 0;
}
