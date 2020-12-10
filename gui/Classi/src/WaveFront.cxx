# include "WaveFront.hxx"
# include "Environment.hxx"

# include <iostream>

using std::cout;
using std::endl;

WaveFront::WaveFront(double x, double y): Polygon(1) 
{
    Polygon[0].x = x, 
    Polygon[0].y = y;
}

WaveFront::WaveFront(Vertex * ver, int N): Polygon(N) 
{
    for(int i = 0; i != N; i++)
    {
        Polygon[i] = ver[i];
    }
}

WaveFront::WaveFront(const WaveFront & wf): Polygon(wf.Polygon) {}


//--------------Methods-----------------


void WaveFront::insertVertex(double x, double y, int i)
{
    std::vector<Vertex>::iterator it;

    it = (i == -1) ? (Polygon.end() + 1) : (Polygon.begin());

    Polygon.insert(it + i, Vertex(x, y));
}


void WaveFront::insertVertex(const Vertex & v, int i)
{
    std::vector<Vertex>::iterator it;

    it = (i == -1) ? (Polygon.end()) + 1 : (Polygon.begin());

    Polygon.insert(it + i, v);
}



bool WaveFront::isColliding(const Vertex & v)
{
    int crosNum = 0;

    for(int i = 0; i != Polygon.size(); i++)
    {
        // If either the vertex are above, or at the left of the point skip it
        if( 
            (Polygon[i].y > v.y && Polygon[i + 1].y > v.y) || 
            (Polygon[i].y < v.y && Polygon[i + 1].y < v.y) ||
            (Polygon[i].x < v.x && Polygon[i + 1].x < v.x)
          )continue;

        // scamming false crossing

        double xcross = (v.y - Polygon[i].y)*(Polygon[i].x - Polygon[i + 1].x)/(Polygon[i].y - Polygon[i + 1].y) + Polygon[i].x;

        crosNum += (xcross > v.x) ? 1 : 0;
    }

    if(crosNum == 0)
    return 0;
    
    return crosNum % 2 == 1;
}


ciclicVector<Vertex> WaveFront::findIntersection()
{
    ciclicVector<Vertex> Ris;

    for(int i = 0; i != Polygon.size() - 2; i++)
    {
        Vertex a = Polygon[i], b = Polygon[i+1];
        double m1 = (b.y - a.y)/(b.x - a.x);

        double xmin = a.x < b.x ? a.x : b.x;
        double xmax = a.x > b.x ? a.x : b.x;
        double ymin = a.y < b.y ? a.y : b.y;
        double ymax = a.y > b.y ? a.y : b.y;

        for(int j = i+2; j < Polygon.size(); j++)
        {
            Vertex c = Polygon[j], d = Polygon[j+1];

            if(a.x == d.x && a.y == d.y)
            continue;

            // All the condition to skip it

            if(
                (c.x > xmax && d.x > xmax) // Tutto a destra
                            ||
                (c.x < xmin && d.x < xmin) // Tutto a sinistra
            )continue;

            if(
                (c.y > ymax && d.y > ymax) // Tutto su
                            ||
                (c.y < ymin && d.y < ymin) // Tutto giu
            )continue;

            // Start computing only if the points are on the opposite
            // sode of the segment

            double ys = a.y + m1*(c.x - a.x);

            bool cSottoSegmento = c.y < ys;

            ys = a.y + m1*(d.x - a.x);

            bool dSottoSegmento = d.y < ys;

            // Se sono entrambi sotto o entrambi sopra skippo
            if(dSottoSegmento == cSottoSegmento)
            continue;

            double m2 = (d.y - c.y)/(d.x - c.x);

            double diff = m1 - m2;

            // If lines are parallel skip this stage
            if(std::abs(diff) < 0.0001)
            continue;

            // Find intersection
            double x = (d.y - a.y + m1*a.x - m2*d.x)/diff;

            double x1min = c.x < d.x ? c.x : d.x;
            double x1max = c.x > d.x ? c.x : d.x;
            double y1min = c.y < d.y ? c.y : d.y;
            double y1max = c.y > d.y ? c.y : d.y;

            // check if the point is inside the segment
            if(
                (x >= xmax) || (x <= xmin)
            )continue;

            double y = a.y + m1*(x - a.x);

            if(
                (y > ymax) || (y < ymin)
            )continue;

            // Add the point
            Vertex Punto(x, y);
            Punto.cellIndex = i+1;
            Punto.dx = j-i;

            Ris.push_back(Punto);
        }
    }

    return Ris;
}