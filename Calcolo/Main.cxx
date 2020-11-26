# include <iostream>
# include <cmath>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

# include "Environment.hxx"

int main()
{
    Environment Foresta;

    Foresta.addFire(45, 45);
    // Foresta.wildfire[0]->Visualize();

    do 
    {   
        Foresta.advance(10);
        Foresta.wildfire[0]->Visualize();
        cout << '\n' << ">>input q to stop";
    } while (cin.get() != 'q');

    //cout << Foresta.findCell(50, 0) << endl;
    


}