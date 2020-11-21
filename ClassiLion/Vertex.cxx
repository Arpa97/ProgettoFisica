# include "Vertex.hxx"

# include <cmath>

Vertex::Vertex(double x, double y): x(x), y(y) {}

Vertex::Vertex(const Vertex & v): x(v.x), y(v.y) {}

//---------------------Metods-------------------------

Vertex Vertex::operator-(const Vertex & v) const
{
    return Vertex(x - v.x, y - v.y);
}

Vertex Vertex::operator+(const Vertex & v) const
{
    return Vertex(x + v.x, y + v.y);
}

Vertex Vertex::operator*(double n) const
{
    return Vertex(n*x, n*y);
}

Vertex Vertex::operator/(double n) const
{
    return Vertex(x/n, y/n);
}


//---------------Funzioni esterne---------------------

double Distanza(const Vertex & v1, const Vertex & v2)
{
    return std::sqrt( std::pow((v1.x - v2.x), 2) + std::pow((v1.y - v2.y), 2) );
}

Vertex operator* (double n, const Vertex & v)
{
    return v*n;
}

Vertex operator/ (double n, const Vertex & v)
{
    return v/n;
}
