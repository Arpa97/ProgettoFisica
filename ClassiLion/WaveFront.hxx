/*********************************************************************
 * 
 * Class for the rappresentation of the fire polygon. It is a 
 * collection of vertex and the name comes from Huygens principle 
 * wich is the core of the model
 * 
 *********************************************************************/
 
# pragma once

# include "Vertex.hxx"

# include <vector>

// Constant that express the maximum distance from two vertices
# define DISTMAX 0.1

struct WaveFront
{
    std::vector<Vertex> Polygon;
     
    //-----------Constructors-------------

    WaveFront(double x = 0, double y = 0);
    WaveFront(Vertex * ver, int N);
    WaveFront(const WaveFront & wf);

    //--------------Methods---------------

    // Method to insert a vertex in a specific position
    void insertVertex(double x, double y, int i = -1);
    void insertVertex(const Vertex & v, int i);

    // Method to check the distance from two points and add another one if the distance is too small
    // i is where to start the checking, so i can iterate the last segment
    void checkDistance();

    // Method to detect collision
    bool isColliding(const Vertex & v);
};
