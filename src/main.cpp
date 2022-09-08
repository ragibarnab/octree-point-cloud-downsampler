#include "point.hpp"
#include "boundary.hpp"
#include "octree.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <iomanip>

using namespace std;

// my short and dirty downsampling technique: recursively collect the stored points of the octree until a certain target depth of the structure
template<typename T>
void downsample(std::shared_ptr<Octree<T>> octree, vector<Point<T>>& out, int target_depth, int depth=0)
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
    std::shared_ptr<Octree<float>> ot = std::make_shared<Octree<float>>(b);

    // inserting points one by one into the tree
    int input_size = 0;
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
            Point<float> p = Point<float>(x,y,z);
            ot->insert(p);
            input_size++;
        }
    }
    infil.close();

    // downsample
    vector<Point<float>> downsampled;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    downsample(ot, downsampled, 9);     // depth: parameter to tune         
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    // write out performance 
    auto runtime_ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout << "Downsampling runtime = " << runtime_ms << "[ms]" << endl;
    int output_size = (int) downsampled.size();
    float percent_downsampled = (1 - ((float) output_size / (float) input_size)) * 100;
    cout << "Downsampling rate = " << setprecision(4) << percent_downsampled << " %" << endl;
                   

    // write output into a file on disk
    ofstream outfile("output.csv");
    if (outfile.is_open())
    {
        outfile << "x,y,z" << endl;
        for (Point<float> p: downsampled)
            outfile << p.x << ',' << p.y << ',' << p.z << endl;
    }
    outfile.close();
    return 0;
}
