# include "WaveFront.hxx"

WaveFront::WaveFront(double x, double y): Polygon(1) 
{
    Polygon[0].x = x, Polygon[0].y = y;
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


void WaveFront::checkDistance()
{

    for(int i = 0; i != Polygon.size(); i++)
    if(Distance(Polygon[i], Polygon[i + 1]) > MAX_DISTANCE)
    {
        insertVertex(
            // Insert the mid point
            (Polygon[i].x + Polygon[i + 1].x)/2,
            (Polygon[i].y + Polygon[i + 1].y)/2,
            i + 1
                    );
     
        // Return back to see if the 
        // mid point inserted is at a right distance
        i--;
    }

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

    return crosNum % 2 == 1;
}
