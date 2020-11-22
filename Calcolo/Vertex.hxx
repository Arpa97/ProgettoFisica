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

    //---------------Methods----------------

    Vertex operator-(const Vertex & v) const;
    Vertex operator+(const Vertex & v) const;
    Vertex operator*(double n) const;
    Vertex operator/(double n) const;
};

//--------------- Non-member functions ---------------------

// Function that computes the distance between two vertices
double Distance(const Vertex & v1, const Vertex & v2);

Vertex operator* (double n, const Vertex & v);
