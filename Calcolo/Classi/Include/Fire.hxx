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
    // Pointer to the class enviroment for taking the ambiental 
    // parameter needed for calculation
    Environment * Forest;

    Fire(Environment * _Forest, double Xi, double Yi);
    Fire(const Fire & f);

    //--------------Methods----------------

    // Method for the spread of fire based Huygens principle
    void Propagate(double dt);

    // Method to compute the increment in position of a particular vertex
    // the resul is stored in val and the vertex is told by the index i
    // used for computing single incrementation value for dynamic timestep evaluation
    void calcPropagation(double * val, int i);

    // Method for getting the RoS and the other par of a vertex signed by an index i 
    // stored in the right cell of the enviroment and put it in an array "par"
    void getParam(double * par, int i);

    // Method to compute the differential arrays for the Richard equation
    ciclicVector<Vertex> calcDiff(const ciclicVector<Vertex> & v);
};
