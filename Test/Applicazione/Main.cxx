# include <iostream>
# include <cmath>

using std::cout;
using std::endl;

# include "Environnement.hxx"

void VisualizzaFuoco(Fire & f)
{
    for(int i = 0; i != f.Polygon.size(); i++)
    cout << "(" << f.Polygon[i].x << ", " << f.Polygon[i].y << ")\t";

    cout << "\n\n";
}

int main()
{
    Environnement Foresta;

    Foresta.addFire(50, 50);

    VisualizzaFuoco(*Foresta.wildfire[0]);

    Foresta.advance();

    VisualizzaFuoco(*Foresta.wildfire[0]);

    return 0;
}