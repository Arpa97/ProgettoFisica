# include <iostream>
# include <cmath>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

# include "Environment.hxx"

void VisualizzaFuoco(Fire & f)
{
    cout << '\n';

    for (int i = 0; i != f.Polygon.size(); i++)
        cout << std::setprecision(4) << std::fixed <<  f.Polygon[i].nextTime << "\t  ";

    cout << '\n';
    for(int i = 0; i != f.Polygon.size(); i++)
    cout << "(" << f.Polygon[i].x << ", " << f.Polygon[i].y << ")\t";

    cout << "\n\n";
}

int main()
{
    Environment Foresta;

    Foresta.addFire(45, 45);
    VisualizzaFuoco(*Foresta.wildfire[0]);

    do 
    {   
        Foresta.advance();
        VisualizzaFuoco(*Foresta.wildfire[0]);
        cout << '\n' << ">>input q to stop";
    } while (cin.get() != 'q');

    //cout << Foresta.findCell(50, 0) << endl;
    


}