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
struct Enviroment
{
    double tetha = 0;
    double U = 0;
};

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

    // Metod for getting the RoS and the other par of a vertex signed by an index i 
    // stored in the right cell of the enviroment and put it in an array "par"
    void getParam(double * par, int i);

    // Metod to compute the differential arrays for the Richard equation
    CiclicContainer<Vertex> calcDiff(const CiclicContainer<Vertex> & v);
};
