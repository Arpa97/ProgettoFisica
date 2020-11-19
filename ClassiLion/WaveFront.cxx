# include "WaveFront.hxx"

WaveFront::WaveFront(double x, double y): Poligon(1) 
{
    Poligon[0].x = x, Poligon[0].y = y;
}

WaveFront::WaveFront(Vertex * ver, int N): Poligon(N) 
{
    for(int i = 0; i != N; i++)
    Poligon[i] = ver[i];
}

WaveFront::WaveFront(const WaveFront & wf): Poligon(wf.Poligon) {}


//--------------Metodi-----------------


void WaveFront::insertVertex(double x, double y, int i)
{
    std::vector<Vertex>::iterator it;

    it = i == -1 ? Poligon.end() + 1 : Poligon.begin();

    Poligon.insert(it + i, Vertex(x, y));
}


void WaveFront::insertVertex(const Vertex & v, int i)
{
    std::vector<Vertex>::iterator it;

    it = i == -1 ? Poligon.end() + 1 : Poligon.begin();

    Poligon.insert(it + i, v);
}


void WaveFront::ceckDistance(int ii)
{

    for(int i = ii; i != Poligon.size() - 1; i++)
    if(Distanza(Poligon[i], Poligon[i + 1]) > DISTMAX)
    {
        insertVertex(
            // Insert the mid point
            (Poligon[i].x + Poligon[i + 1].x)/2,
            (Poligon[i].y + Poligon[i + 1].y)/2,
            i + 1
        );
    
        // Return back to see if the 
        // mid point inserted is at a right distance
        i--;
    }

    int n = Poligon.size() - 1;

    // Inserting between the last segment
    if(Distanza(Poligon[n], Poligon[0]) > DISTMAX)
    {
        insertVertex(
            // Insert the mid point
            (Poligon[n].x + Poligon[0].x)/2,
            (Poligon[n].y + Poligon[0].y)/2,
            n + 1
        );

        ceckDistance(n - 2);
    }

}


bool WaveFront::isColliding(const Vertex & v)
{
    int crosNum = 0;
    int n = Poligon.size();

    for(int i = 0; i != n - 1; i++)
    {
        // If either the vertex are above, or at the left of the point skip it
        if( 
            (Poligon[i].y > v.y && Poligon[i + 1].y > v.y) || 
            (Poligon[i].y < v.y && Poligon[i + 1].y < v.y) ||
            (Poligon[i].x < v.x && Poligon[i + 1].x < v.x)
        )continue;

        // scamming false crossing

        double xcross = (v.y - Poligon[i].y)*(Poligon[i].x -Poligon[i + 1].x)/(Poligon[i].y -Poligon[i + 1].y) + Poligon[i].x;

        crosNum += xcross > v.x ? 1 : 0;
    }

    // cecking the last segment
    if( 
        !(Poligon[n - 1].y > v.y && Poligon[0].y > v.y) && 
        !(Poligon[n - 1].y < v.y && Poligon[0].y < v.y) &&
        !(Poligon[n - 1].x < v.x && Poligon[0].x < v.x)
    )
    {
        // scamming false crossing

        double xcross = (v.y - Poligon[n - 1].y)*(Poligon[n - 1].x -Poligon[0].x)/(Poligon[n - 1].y -Poligon[0].y) + Poligon[n - 1].x;

        crosNum += xcross > v.x ? 1 : 0;
    }

    return crosNum % 2 == 1;
}