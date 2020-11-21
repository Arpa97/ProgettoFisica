# include "Vertex.hxx"

# include <cmath>

Vertex::Vertex(double x, double y): x(x), y(y) {}

Vertex::Vertex(const Vertex & v): x(v.x), y(v.y) {}


//---------------Funzioni esterne---------------------

double Distance(const Vertex & v1, const Vertex & v2)
{
    return std::sqrt( std::pow((v1.x - v2.x), 2) + std::pow((v1.y - v2.y), 2) );
}