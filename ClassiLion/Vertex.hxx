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

    //---------------Metods----------------

    Vertex operator-(const Vertex & v) const;
    Vertex operator+(const Vertex & v) const;
    Vertex operator*(double n) const;
    Vertex operator/(double n) const;
};

//---------------Funzioni esterne---------------------

// Funzione per il calcolo della distanza tra due vertici
double Distanza(const Vertex & v1, const Vertex & v2);

Vertex operator* (double n, const Vertex & v);
Vertex operator/ (double n, const Vertex & v);