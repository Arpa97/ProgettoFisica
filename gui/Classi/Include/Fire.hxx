/*********************************************************************
 * 
 * Class for the rappresentation of the fire, it will be an extension
 * of the class WaveFront and will perform calculations for the
 * fire expansion.
 * 
 *********************************************************************/

# pragma once

# include "WaveFront.hxx"

class Environment;

struct Fire : public WaveFront
{
public:
    // Pointer to the class enviroment for taking the ambiental 
    // parameter needed for calculation
    static Environment * Forest;

    Fire(double Xi, double Yi);
    Fire(const Fire & f);

    //--------------Methods----------------
    static void setEnvironment(Environment* _Forest);

    // Method for the spread of fire based on Huygens principle
    void Propagate(double dt);
    void Propagate_withoutHeap(double dt);

    // Method to compute the increment in position of a particular vertex
    // the resul is stored in val and the vertex is told by the index i
    // used for computing single incrementation value for dynamic timestep evaluation
    void calcVelocity(int i);
    void calcTime(int i);

    // Methods to initialize the propagation in all verticies, and time
    void calcVelocities();
    void calcTimes();

    // Method to check the distance between two points and add another one if the distance is too small
    // i is where to start the checking, so i can iterate the last segment
    void checkDistance(bool heap = true);
    void checkEdges();
    void checkBorder();

    // Method to compute the differential arrays for the Richard equation
    ciclicVector<Vertex> calcDiff(const ciclicVector<Vertex> & v);

    // Method for visualize the vertex information
    void Visualize();

    // Method to delete verteces
    void DeleteVertex(int n);
    void DeleteVertex(int start, int end);
};
