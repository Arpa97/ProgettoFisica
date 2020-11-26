#include "Fire.hxx"
#include "Environment.hxx"

#include <cmath>
#include <iostream>
#include <iomanip>

Fire::Fire(Environment * _Forest, double Xi, double Yi): Forest(_Forest)
{
    Polygon.resize(10);
    
    // Creation of a little ellipse centered on the point rotated by
    // the direction of the wind

    Cell * cell = Forest->getCell(Xi, Yi);
    double tetha = Forest->getTheta();

    // Support variable for the rotation
    double x1, y1;

    //std::cerr << cell->a << ' ' << cell->b << '\n';
    for(int i = 0; i != 10; i++)
    {
        // Divided by 100 because the initial ellipse is needed to be small
        x1 = cell->a * std::cos(i*M_PI/5)/100;
        y1 = cell->b * std::sin(i*M_PI/5)/100;

        x1 = x1 * std::cos(tetha) + y1 * std::sin(tetha);
        y1 = y1 * std::cos(tetha) - x1 * std::sin(tetha);

        Polygon[i].x = Xi + x1;
        Polygon[i].y = Yi + y1;

        //std::cerr << Polygon[i].x << ' ' << Polygon[i].y << '\n';
        Polygon[i].cellIndex = Forest->findCell(Polygon[i]);
    }
    std::cerr << '\n';
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
    {
        Polygon[i].x = f.Polygon[i].x;
        Polygon[i].y = f.Polygon[i].y;
        Polygon[i].cellIndex = Forest->findCell(Polygon[i]);
        calcPropagation(i);
        calcTime(i);
    }
}



// ----------------Methods-------------------

void Fire::Propagate(double dt)
{
    //Cell * cella;
    //double tetha = Forest->getTheta();
    //ciclicVector<Vertex> Diff = calcDiff(Polygon);
    //
    //double Ct = std::cos(tetha), St = std::sin(tetha);

    //double At, Bt, num1, num2, den;

    //for(int i = 0; i != Polygon.size(); i++)
    //{	
    //    cella = Forest->getCell(Polygon[i]);

    //    // Computing the vertex differential for propagating the front
    //    At = cella->a * (Diff[i].x * St + Diff[i].y * Ct);
    //    Bt = cella->b * (Diff[i].y * St - Diff[i].x * Ct);

    //    num1 = cella->a * At * Ct + cella->b * Bt * St;
    //    num2 = cella->b * Bt * Ct - cella->a * At * St;

    //    den = std::sqrt(At*At + Bt*Bt);

    //    Polygon[i].x += (num1/den + cella->c * St)*dt;
    //    Polygon[i].y += (num2/den + cella->c * Ct)*dt;
    //}

    int iChange;
    for (int i = 0; i != Polygon.size(); i++)
    {
        Polygon[i].x += Polygon[i].dx * dt;
        Polygon[i].y += Polygon[i].dy * dt;

        if (Forest->time >= Polygon[i].nextTime)
        {
            std::cerr << (Forest->time == Polygon[i].nextTime) << '\n';      //mi aspetto che ce ne sia solo uno che va dentro questo if, e che i tempi siano proprio uguali
            iChange = i;
        }
    }
    Polygon[iChange].cellIndex = Forest->findCell(Polygon[iChange]);
    calcPropagation(iChange);
    calcTime(iChange);
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

    double At, Bt, num1, num2, den;
    double Ct = std::cos(Forest->getTheta());
    double St = std::sin(Forest->getTheta());
    Vertex Diff = (Polygon[i + 1] - Polygon[i - 1]) / 2;
    //std::cerr << Diff.x << ' ' << Diff.y << '\n';

    At = cella->a * (Diff.x * St + Diff.y * Ct);
    Bt = cella->b * (Diff.y * St - Diff.x * Ct);

    num1 = cella->a * At * Ct + cella->b * Bt * St;
    num2 = cella->b * Bt * Ct - cella->a * At * St;

    den = std::sqrt(At * At + Bt * Bt);

    Polygon[i].dx = num1 / den + cella->c * St;
    Polygon[i].dy = num2 / den + cella->c * Ct;
    //std::cerr << "( " << Polygon[i].dx << ", " << Polygon[i].dy << " )" << '\t';
}



void Fire::calcTime(int i)
{
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
    if (dx < 0 && cellX > 0) cellX -= 0.0001;
    if (dy < 0 && cellY > 0) cellY -= 0.0001;

    double timeX = (cellX - Polygon[i].x) / dx;
    double timeY = (cellY - Polygon[i].y) / dy;

    double dt = std::min(timeX, timeY);
    double nextTime = Forest->time + dt;

    //std::cerr << dx << ' ' << dy << ' ' << dt << ' ' << nextTime << '\n';

    Polygon[i].nextTime = nextTime;
    Forest->timeHeap.push(nextTime);

    //std::cerr << nextTime << '\n';
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
