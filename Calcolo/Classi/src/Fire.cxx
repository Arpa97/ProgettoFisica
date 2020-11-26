#include "Fire.hxx"
#include "Environment.hxx"

#include <cmath>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

Fire::Fire(Environment * _Forest, double Xi, double Yi): Forest(_Forest)
{
    Polygon.resize(10);
    
    // Creation of a little ellipse centered on the point rotated by
    // the direction of the wind

    Cell * cell = Forest->getCell(Xi, Yi);
    double tetha = Forest->getTheta();

    // Support variable for the rotation
    double x1, y1;

    for(int i = 0; i != 10; i++)
    {
        // Divided by 100 because the initial ellipse is needed to be small
        x1 = cell->a * std::cos(i*M_PI/5)/GRID_SIDE;
        y1 = cell->b * std::sin(i*M_PI/5)/GRID_SIDE;

        x1 = x1 * std::cos(tetha) + y1 * std::sin(tetha);
        y1 = y1 * std::cos(tetha) - x1 * std::sin(tetha);

        Polygon[i].x = Xi + x1;
        Polygon[i].y = Yi + y1;

        Polygon[i].cellIndex = Forest->findCell(Polygon[i]);
    }

    // Calcolation of the dynamical timestep for the initial vertex
    for (int i = 0; i != 10; i++)
    {
        calcPropagation(i);
        calcTime(i);
    }
    
}


Fire::Fire(const Fire & f): Forest(f.Forest)
{
    Polygon.resize(f.Polygon.size());
    for (int i = 0; i != f.Polygon.size(); i++)
    // Al posto di 3 righe così è più facile e non vanno chiamati membri
    Polygon[i] = f.Polygon[i];
}



// ----------------Methods-------------------

void Fire::Propagate(double dt)
{
    int iChange = -1;
    
    for (int i = 0; i != Polygon.size(); i++)
    {
        Polygon[i].x += Polygon[i].dx * dt;
        Polygon[i].y += Polygon[i].dy * dt;

        // Find the one that change cell exatly in that time
        if (Polygon[i].nextTime != -1 && Forest->time >= Polygon[i].nextTime)
        {
            iChange = i;
        }
    }

    // Calculation for the one that changes cell
    if(iChange != -1)
    {
        Polygon[iChange].cellIndex = Forest->findCell(Polygon[iChange]);
        calcPropagation(iChange);
        calcTime(iChange);
    }

    // Checking distance from verteces
    checkDistance();
}



void Fire::calcPropagation(double * val, int i)
{
    Cell * cella = Forest->getCell(Polygon[i]);

    double At, Bt, num1, num2, den;
    double Ct = std::cos(Forest->getTheta());
    double St = std::sin(Forest->getTheta());
    Vertex Diff = (Polygon[i + 1] - Polygon[i - 1])/2; 

    At = cella->a * (Diff.x * St + Diff.y * Ct);
    Bt = cella->b * (Diff.y * St - Diff.x * Ct);

    num1 = cella->a * At * Ct + cella->b * Bt * St;
    num2 = cella->b * Bt * Ct - cella->a * At * St;

    den = std::sqrt(At*At + Bt*Bt);

    val[0] =  num1/den + cella->c * St;
    val[1] =  num2/den + cella->c * Ct;
}



void Fire::calcPropagation(int i)
{
    Cell* cella = Forest->getCell(Polygon[i]);

    if (cella == Forest->nullFuel)
    {
        Polygon[i].dx = Polygon[i].dy = 0;
        return;
    }

    double At, Bt, num1, num2, den;
    double Ct = std::cos(Forest->getTheta());
    double St = std::sin(Forest->getTheta());
    Vertex Diff = (Polygon[i + 1] - Polygon[i - 1]) / 2;

    At = cella->a * (Diff.x * St + Diff.y * Ct);
    Bt = cella->b * (Diff.y * St - Diff.x * Ct);

    num1 = cella->a * At * Ct + cella->b * Bt * St;
    num2 = cella->b * Bt * Ct - cella->a * At * St;

    den = std::sqrt(At * At + Bt * Bt);

    Polygon[i].dx = num1 / den + cella->c * St;
    Polygon[i].dy = num2 / den + cella->c * Ct;
}



void Fire::calcTime(int i)
{
    if (Polygon[i].cellIndex == -1)
    {
        Polygon[i].nextTime = -1;
        return;
    }

    double dx = Polygon[i].dx;
    double dy = Polygon[i].dy;

    int step = GRID_SIDE / CELL_SIDE;
    int _j = Polygon[i].cellIndex % step;
    int _i = (Polygon[i].cellIndex - _j) / step;
    if (dx > 0) _j += 1;
    if (dy > 0) _i += 1;

    //Position of the cell borders in the direction in which the vertex is moving
    double cellX = _j * CELL_SIDE;
    double cellY = _i * CELL_SIDE;

    //Subtract a little value to make sure that the vertex changes cell and does not remain on the border
    if (dx < 0) cellX -= 0.0001;
    if (dy < 0) cellY -= 0.0001;

    double timeX = (cellX - Polygon[i].x) / dx;
    double timeY = (cellY - Polygon[i].y) / dy;

    double dt = std::min(timeX, timeY);
    double nextTime = Forest->time + dt;

    if(nextTime > 100000)
    {
        cout << "cellaFutura: [" << _i << "][" << _j << "]  ";
        cout << "Varizione tempo = " << dt << endl;
    }

    Polygon[i].nextTime = nextTime;
    Forest->timeHeap.push(nextTime);
}



void Fire::checkDistance()
{
    for (int i = 0; i != Polygon.size(); i++)
        if (Distance(Polygon[i], Polygon[i + 1]) > MAX_DISTANCE)
        {
            insertVertex(
                // Insert the mid point
                (Polygon[i].x + Polygon[i + 1].x) / 2,
                (Polygon[i].y + Polygon[i + 1].y) / 2,
                i + 1
            );

            // Calculation of the propagation parameter
            Polygon[i + 1].cellIndex = Forest->findCell(Polygon[i + 1]);
            calcPropagation(i + 1);
            calcTime(i + 1);

            // Return back to see if the 
            // mid point inserted is at a right distance
            i--;
        }
}



ciclicVector<Vertex> Fire::calcDiff(const ciclicVector<Vertex> & v)
{
    ciclicVector<Vertex> Diff(Polygon.size());

    Diff[0] = (Polygon[Polygon.size() - 1] - Polygon[1])/2;

    for(int i = 1; i != Polygon.size(); i++)
    Diff[i] = (Polygon[i + 1] - Polygon[i - 1])/2;

    return Diff;
}

void Fire::Visualize()
{
    cout << '\n';

    int step = GRID_SIDE/CELL_SIDE;
    int cella;

    for (int i = 0; i != Polygon.size(); i++)
    {
        cella = Polygon[i].cellIndex;

        cout << "Vertice" << i << " = ";
        cout << std::setprecision(4) << "(" << Polygon[i].x << ", " << Polygon[i].y << ")";
        cout << std::setw(10);
        cout << "Cella [" << (cella - (cella % step))/step << "][" << cella%step << "]";
        cout << std::setw(10);
        cout << "tSucc = " << std::setprecision(4) << std::fixed <<  Polygon[i].nextTime  << "\t";
        cout << std::setw(10);
        cout << "Propagazione = " << std::setprecision(4) << "(" << Polygon[i].dx << ", " << Polygon[i].dy << ")";
        cout << std::endl;
    }

    cout << "\n\n";
}