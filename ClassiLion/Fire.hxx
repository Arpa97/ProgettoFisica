/*********************************************************************
 * 
 * Class for the rappresentation of the fire, it will be an extension
 * of the class WaveFront and is going to make the calculation fro the
 * expansion etcetera
 * 
 *********************************************************************/

# pragma once

# include "WaveFront.hxx"

// For future class that is needed
class Enviroment;

struct Fire : public WaveFront
{
    // Pointer to the class enviroment for taking the ambiental 
    // parameter needed for calculation
    Enviroment * Forest;

    Fire(Enviroment * Forest, double Xi, double Yi);
    Fire(const Fire & f);

    //--------------Metods----------------

    // Metod for the spread of fire based Huygens principle
    void Propagate(double dt);

    // Metod for computing the a, b and c of the ellipses in a 
    // particular vertex signed by an index i
    double * elipsesAxises(int i);

    // Metod for getting the RoS of a vertex signed by an index i 
    // stored in the right cell of the enviroment
    double getRoS(int i);

    // Metod to compute the differential arrays for the Richard equation
    CiclicContainer<Vertex> calcDiff(const CiclicContainer<Vertex> & v);
};
