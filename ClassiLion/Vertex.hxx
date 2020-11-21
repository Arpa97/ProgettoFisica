/*********************************************************************
 * 
 * Class for the rappresentation of the verteces of a polygon that
 * will define the fire in the model
 * 
 *********************************************************************/


# pragma once

struct Vertex
{
    double x;
    double y;


    Vertex(double x = 0, double y = 0);
    Vertex(const Vertex & v);
};

//--------------- Non member functions ---------------------

// Function that calculates the distance between two vertices.
double Distance(const Vertex & v1, const Vertex & v2);