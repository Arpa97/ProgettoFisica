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
    double (*composizione)[2] = new double[3][2] { {1, .5}, {13, .2}, {7, .3} };
    Environment* foresta = new Environment(composizione, 3);


    int counter[4] = { 0, 0, 0, 0 };
    int step = GRID_SIDE / CELL_SIDE;

    for (int i = 0; i != step; i++)
    {
        for (int j = 0; j != step; j++)
        {
            if (foresta->grid[i][j]->fuelIndex == 1) counter[0]++;
            else if (foresta->grid[i][j]->fuelIndex == 13) counter[1]++;
            else if (foresta->grid[i][j]->fuelIndex == 7) counter[2]++;
            else counter[3]++;
        }
    }

    cout << "Fuel 1: " << counter[0] << "/" << step * step << " = " << counter[0] / (step * step + .0) << '\n';
    cout << "Fuel 13: " << counter[1] << "/" << step * step << " = " << counter[1] / (step * step + .0) << '\n';
    cout << "Fuel 7: " << counter[2] << "/" << step * step << " = " << counter[2] / (step * step + .0) << '\n';
    cout << "Altri: " << counter[3] << '\n';

    



    //Foresta.addFire(50, 50);
    // Foresta.wildfire[0]->Visualize();
    //for (int i = 0; i < cyclestotest; i++) {
    //    if (i == 10 || i == 100 || i == 200) {
    //        Foresta.addFire(50, i);
    //        Foresta.setU((double)i/10);
    //        Foresta.setTheta(-2);
    //    }
    //    Foresta.advance(1);
    //    Foresta.wildfire[0]->Visualize();
    //}
    
    /*do 
    {   
        Foresta.advance();
        Foresta.wildfire[0]->Visualize();
        cout << '\n' << ">>input q to stop";
    } while (cin.get() != 'q');

    //cout << Foresta.findCell(50, 0) << endl;
    */
}