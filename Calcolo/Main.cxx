# include <iostream>
# include <cmath>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

# include "Environment.hxx"
#include "Definitions.hxx"

int main()
{
    int cyclestotest = 1000;
    
    Environment Foresta;

    Foresta.addFire(5, 5);
    // Foresta.wildfire[0]->Visualize();
    for (int i = 0; i < cyclestotest; i++) {
        if (i == 500) {
            Foresta.setU(10.0);
            Foresta.setTheta(-2);
        }
        Foresta.advance();
        Foresta.wildfire[0]->Visualize();
    }
    
    /*do 
    {   
        Foresta.advance();
        Foresta.wildfire[0]->Visualize();
        cout << '\n' << ">>input q to stop";
    } while (cin.get() != 'q');

    //cout << Foresta.findCell(50, 0) << endl;
    */
}