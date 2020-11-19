/*********************************************************************
 * 
 * Class for the rappresentecion of the polygon of the fire, is a 
 * collection of vertex and the name wave came from the method of 
 * Huygens that is at the bottom of the model
 * 
 *********************************************************************/

# pragma once

# include "Vertex.hxx"

# include <vector>

// Constant that express the maximum distance from two vertices
# define DISTMAX 0.1

struct WaveFront
{
    std::vector<Vertex> Poligon;

    //-----------Constructors-------------

    WaveFront(double x = 0, double y = 0);
    WaveFront(Vertex * ver, int N);
    WaveFront(const WaveFront & wf);

    //--------------Methods---------------

    // Metod to insert a vertex in a specific position
    void insertVertex(double x, double y, int i = -1);
    void insertVertex(const Vertex & v, int i);

    // Metod to ceck the distance from two points and ad another if the distance is too small
    // i is where to start the cecking, so i can iterate the last segment
    void checkDistance(int ii = 0);

    // Metod to detect collision
    bool isColliding(const Vertex & v);
};
