# include "WaveFront.hxx"
# include "Environment.hxx"

# include <iostream>

using std::cout;
using std::endl;

WaveFront::WaveFront(double x, double y): Polygon(1) 
{
    Polygon[0].x = x, 
    Polygon[0].y = y;
    area = 0;
}

WaveFront::WaveFront(Vertex * ver, int N): Polygon(N) 
{
    for(int i = 0; i != N; i++)
    {
        Polygon[i] = ver[i];
    }
    area = 0;
}

WaveFront::WaveFront(const WaveFront & wf): Polygon(wf.Polygon), area(wf.area) {}


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


Vertex WaveFront::findIntersection(int start)
{
    Vertex Point = Vertex(0, 0);

    for(int i = start; i < Polygon.size(); i++)
    {
        Vertex a = Polygon[i], b = Polygon[i+1];
        double m1 = (b.y - a.y)/(b.x - a.x);
        double q1 = a.y - m1 * a.x;

        double xmin = a.x < b.x ? a.x : b.x;
        double xmax = a.x > b.x ? a.x : b.x;
        double ymin = a.y < b.y ? a.y : b.y;
        double ymax = a.y > b.y ? a.y : b.y;


        if(a.x != b.x)
            for (int t = 0; t < std::min(10, (int)Polygon.size() - 2); t++)
            {
                int j = (i + 2 + t) % Polygon.size();

                Vertex c = Polygon[j], d = Polygon[j + 1];

                if (a.x == d.x && a.y == d.y)
                    continue;

                // All the condition to skip it

                if (
                    (c.x > xmax && d.x > xmax) // Tutto a destra
                    ||
                    (c.x < xmin && d.x < xmin) // Tutto a sinistra
                    ||
                    (c.y > ymax && d.y > ymax) // Tutto su
                    ||
                    (c.y < ymin && d.y < ymin) // Tutto giu
                    )continue;

                // Start computing only if the points are on the opposite
                // sides of the segment

                double ys = m1 * c.x + q1;

                bool cSottoSegmento = c.y < ys;

                ys = m1 * d.x + q1;

                bool dSottoSegmento = d.y < ys;

                // Se sono entrambi sotto o entrambi sopra skippo
                if (dSottoSegmento == cSottoSegmento)
                    continue;

                if (c.x == d.x)
                {
                    double x = c.x;
                    double y = m1 * x + q1;

                    // Add the point
                    Point = Vertex(x, y);

                    // Index of the point where the intersection is
                    Point.cellIndex = i + 1;

                    // Index of the point where the intersection end
                    Point.dx = j + 1;

                    return Point;
                }

                else
                {
                    double m2 = (d.y - c.y) / (d.x - c.x);
                    double q2 = d.y - m2 * d.x;

                    double diff = m1 - m2;

                    // If lines are parallel skip this stage
                    if (std::abs(diff) < 0.0001)
                        continue;

                    // Find intersection
                    double x = (q2 - q1) / diff;

                    //double x1min = c.x < d.x ? c.x : d.x;
                    //double x1max = c.x > d.x ? c.x : d.x;
                    //double y1min = c.y < d.y ? c.y : d.y;
                    //double y1max = c.y > d.y ? c.y : d.y;

                    // check if the point is inside the segment
                    if (
                        (x >= xmax) || (x <= xmin)
                        )continue;

                    double y = m1 * x + q1;

                    // Add the point
                    Point = Vertex(x, y);
                    // Index of the point where the intersection is
                    Point.cellIndex = i + 1;

                    // Index of the point where the intersection end
                    Point.dx = j + 1;

                    return Point;
                }
            }
       
        //if a.x == b.x (points on the border)line is of the type x=k
        else
            for (int t = 0; t < std::min(10, (int)Polygon.size() - 2); t++)
            {
                int j = (i + 2 + t) % Polygon.size();

                Vertex c = Polygon[j], d = Polygon[j + 1];

                //Skip segments on the border too 
                if (c.x == d.x) continue;

                if (a.x == d.x && a.y == d.y) continue;

                if (
                    (c.x > a.x && d.x > a.x) // Tutto a destra
                    ||
                    (c.x < a.x && d.x < a.x) // Tutto a sinistra
                    ||
                    (c.y > ymax && d.y > ymax) // Tutto su
                    ||
                    (c.y < ymin && d.y < ymin) // Tutto giu
                    )continue;

                double m2 = (d.y - c.y) / (d.x - c.x);
                double q2 = d.y - m2 * d.x;

                // Find intersection
                double x = a.x;
                double y = m2 * x + q2;

                if(
                    (y > ymax) || (y < ymin)
                )continue;

                // Add the point
                Point = Vertex(x, y);

                // Index of the point where the intersection is
                Point.cellIndex = i + 1;

                // Index of the point where the intersection end
                Point.dx = j + 1;

                return Point;
            }
    }
    Point.cellIndex = -1;
    return Point;
}

void WaveFront::calcArea()
{
    area = 0;
    for (int i = 1; i <= Polygon.size(); i++)
    {
        area += Polygon[i].x * (Polygon[i + 1].y - Polygon[i - 1].y);
    }
    area /= 2;
}