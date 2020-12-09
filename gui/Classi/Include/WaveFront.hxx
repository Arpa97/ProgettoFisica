/*********************************************************************
 * 
 * Class for the rappresentation of the fire polygon. It is a 
 * collection of vertex and the name comes from Huygens principle 
 * wich is the core of the model
 * 
 *********************************************************************/
 
# pragma once

# include "Vertex.hxx"

# include "CiclicVector.hxx"
# include "Definitions.hxx"

class Environment;

struct WaveFront
{
    ciclicVector<Vertex> Polygon;
     
    //-----------Constructors-------------

    WaveFront() {}
    WaveFront(double x, double y);
    WaveFront(Vertex * ver, int N);
    WaveFront(const WaveFront & wf);

    //--------------Methods---------------

    // Method to insert a vertex in a specific position
    void insertVertex(double x, double y, int i = -1);
    void insertVertex(const Vertex & v, int i);

    // Method to detect collision
    bool isColliding(const Vertex & v);

    ciclicVector<Vertex> findIntersection();
};
