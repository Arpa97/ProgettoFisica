#include "Fire.hxx"
#include "Environment.hxx"

#include <cmath>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

Environment* Fire::Forest;

Fire::Fire(double Xi, double Yi)
{
    Polygon.resize(8);
    
    // Creation of a little ellipse centered on the point rotated by
    // the direction of the wind
    Cell * cell = Forest->getCell(Xi, Yi);
    double tetha = Forest->getTheta();

    // Support variable for the rotation
    double x1, y1;

    for(int i = 0; i != 8; i++)
    {
        // Divided by 100 because the initial ellipse is needed to be small
        //x1 = cell->a * std::cos(i*M_PI/5)/GRID_SIDE;
        //y1 = cell->b * std::sin(i*M_PI/5)/GRID_SIDE;
        x1 = std::cos(i * M_PI / 4) / GRID_SIDE;
        y1 = std::sin(i * M_PI / 4) / GRID_SIDE;

        //x1 = x1 * std::cos(tetha) + y1 * std::sin(tetha);
        //y1 = y1 * std::cos(tetha) - x1 * std::sin(tetha);

        Polygon[i].x = Xi + x1;
        Polygon[i].y = Yi + y1;

        Polygon[i].cellIndex = Forest->findCell(Polygon[i]);
    }

    // Calcolation of the dynamical timestep for the initial verteces
    for (int i = 0; i != 8; i++)
    {
        calcVelocity(i);
        calcTime(i);
    }
}


Fire::Fire(const Fire & f)
{
    Polygon.resize(f.Polygon.size());
    for (int i = 0; i != f.Polygon.size(); i++)
    // Al posto di 3 righe così è più facile e non vanno chiamati membri
    Polygon[i] = f.Polygon[i];
}


// ----------------Methods-------------------
void Fire::setEnvironment(Environment* _Forest)
{
    Fire::Forest = _Forest;
}

void Fire::Propagate(double dt)
{
    //int iChange = -1;
    
    for (int i = 0; i != Polygon.size(); i++)
    {
        Polygon[i].x += Polygon[i].dx * dt;
        Polygon[i].y += Polygon[i].dy * dt;

        // Find the one that changes cell exactly in that time
        // if (Polygon[i].nextTime != -1 && Forest->time >= Polygon[i].nextTime)
        // {
        //     iChange = i;
        //     std::cerr << iChange << ", ";
        // }

        if (Polygon[i].x < 0)
            Polygon[i].x = 0;
        if (Polygon[i].y < 0)
            Polygon[i].y = 0;
        if (Polygon[i].x > GRID_SIDE)
            Polygon[i].x = GRID_SIDE;
        if (Polygon[i].y > GRID_SIDE)
            Polygon[i].y = GRID_SIDE;
    }

    // Calculation for the one that changes cell
    // if(iChange != -1)
    // {
    //     Polygon[iChange].cellIndex = Forest->findCell(Polygon[iChange]);
    //     calcVelocity(iChange);
    //     calcTime(iChange);
    // }

    // Checking intersection and distance from verteces
    checkEdges();
    checkDistance();
    checkBorder();
}

void Fire::Propagate_withoutHeap(double dt)
{
    for (int i = 0; i != Polygon.size(); i++)
    {
        Polygon[i].x += Polygon[i].dx * dt;
        Polygon[i].y += Polygon[i].dy * dt;
        Polygon[i].cellIndex = Forest->findCell(Polygon[i]);
    }

    for (int i = 0; i != Polygon.size(); i++)
    {
        calcVelocity(i);
    }
    checkDistance(false);
}


//void Fire::calcVelocity(int i)
//{
//    Cell* cella = Forest->getCell(Polygon[i]);
//
//    if (cella == Forest->nullFuel)
//    {
//        Polygon[i].dx = Polygon[i].dy = 0;
//        return;
//    }
//
//    double At, Bt, num1, num2, den;
//    double Ct = std::cos(Forest->getTheta());
//    double St = std::sin(Forest->getTheta());
//    Vertex Diff = (Polygon[i + 1] - Polygon[i - 1]) / 2;
//
//    At = cella->a * (Diff.x * St + Diff.y * Ct);
//    Bt = cella->b * (Diff.y * St - Diff.x * Ct);
//
//    num1 = cella->a * At * Ct + cella->b * Bt * St;
//    num2 = cella->b * Bt * Ct - cella->a * At * St;
//
//    den = std::sqrt(At * At + Bt * Bt);
//
//    if (num1 / den + cella->c * St > 1e3 || num1 / den + cella->c * St < -1 || num2 / den + cella->c * Ct >1e3 || num2 / den + cella->c * Ct < -1)
//        throw;
//
//    Polygon[i].dx = num1 / den + cella->c * St;
//    Polygon[i].dy = num2 / den + cella->c * Ct;
//}

void Fire::calcVelocity(int i)
{
    Cell* cella = Forest->getCell(Polygon[i]);

    if (cella == Forest->nullFuel)
    {
        Polygon[i].dx = Polygon[i].dy = 0;
        return;
    }


    double aspect = M_PI_2;
    if(std::abs(cella->AspVect.y) > 1E-7)
    aspect = std::atan(cella->AspVect.x/cella->AspVect.y);

    double tanSlo = std::sqrt(cella->AspVect.x*cella->AspVect.x + cella->AspVect.y*cella->AspVect.y);
    double C = 7.47 * exp(-0.133 * pow(cella->FuelType[cella->fuelIndex]->params[2], 0.55));
    double A = 5.275 * pow(cella->FuelType[cella->fuelIndex]->params[0], -0.3);
    double B = 0.02526 * pow(cella->FuelType[cella->fuelIndex]->params[2], 0.54);
    double theta = Forest->getTheta();

    double MaxDirX, MaxDirY;

    MaxDirX = C*std::pow(Forest->getU(), B)*std::sin(theta - aspect);
    MaxDirY = C*std::pow(Forest->getU(), B)*std::cos(theta - aspect) + A*tanSlo*tanSlo;

    if(std::abs(MaxDirY) > 1E-7)
    theta = std::atan(MaxDirX/MaxDirY) - aspect - M_PI_2;
    else 
    theta = -aspect-M_PI_2;

    cout << theta << endl;

    double At, Bt, num1, num2, den;
    double Ct = std::cos(theta);
    double St = std::sin(theta);
    Vertex diff = (Polygon[i + 1] - Polygon[i - 1]) / 2;


    At = cella->a * (diff.x * St + diff.y * Ct);
    Bt = cella->b * (diff.y * St - diff.x * Ct);

    num1 = cella->a * At * Ct + cella->b * Bt * St;
    num2 = cella->b * Bt * Ct - cella->a * At * St;

    den = std::sqrt(At * At + Bt * Bt);

    if (num1 / den + cella->c * St > 1e3 || num1 / den + cella->c * St < -1 || num2 / den + cella->c * Ct >1e3 || num2 / den + cella->c * Ct < -1)
        throw;

    double Xt = num1 / den + cella->c * St;
    double Yt = num2 / den + cella->c * Ct;

    Polygon[i].dx = Xt;
    Polygon[i].dy = Yt;
}

void Fire::calcVelocities()
{
    for(int i = 0; i != Polygon.size(); i++)
    this->calcVelocity(i);
}

void Fire::calcTimes()
{
    for(int i = 0; i != Polygon.size(); i++)
    this->calcTime(i);
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
    if (dx > 0) _i += 1;
    if (dy > 0) _j += 1;

    //Position of the cell borders in the direction in which the vertex is moving
    double cellX = _i * CELL_SIDE + 0.0001;
    double cellY = _j * CELL_SIDE + 0.0001;

    //Subtract a little value to make sure that the vertex changes cell and does not remain on the border
    if (dx < 0) cellX -= 0.0001;
    if (dy < 0) cellY -= 0.0001;

    double timeX = (cellX - Polygon[i].x) / dx;
    double timeY = (cellY - Polygon[i].y) / dy;

    if (abs(dy) < 1e-5)
        timeY = 1e10;
    if (abs(dx) < 1e-5)
        timeX = 1e10;

    double dt = std::min(timeX, timeY);
    if (dx == 0) dt = timeY;
    if (dy == 0) dt = timeX;

    // For ensure that the fire doesn't stay still
    if(dt < 1E-6) dt = 1E-4;

    Polygon[i].nextTime = Forest->time + dt;
    Forest->timeHeap.push(Forest->time + dt);
}



void Fire::checkDistance(bool heap)
{
    for (int i = 0; i != Polygon.size(); i++)
    {
        if (Polygon[i].cellIndex == -1 && Polygon[i + 1].cellIndex == -1) continue;

        if (Distance(Polygon[i], Polygon[i + 1]) > MAX_DISTANCE)
        {
            insertVertex(
                // Insert the mid point
                (Polygon[i].x + Polygon[i + 1].x) / 2,
                (Polygon[i].y + Polygon[i + 1].y) / 2,
                i + 1
            );

            // Calculation of the propagation parameter
            // Polygon[i + 1].cellIndex = Forest->findCell(Polygon[i + 1]);
            // calcVelocity(i + 1);
            // calcVelocity(i);
            // calcVelocity(i + 2);
            // if (heap)
            // {
            //     Forest->timeHeap.deleteValue(Polygon[i].nextTime);
            //     Forest->timeHeap.deleteValue(Polygon[i+2].nextTime);
            //     calcTime(i + 1);
            //     calcTime(i);
            //     calcTime(i + 2);
            // }

            // Return back to see if the 
            // mid point inserted is at a right distance
            i--;
        }
    }
}

void Fire::checkEdges()
{
    int index = 1;

    while (index < Polygon.size())
    {
        Vertex Int = findIntersection(index - 1);

        if (Int.cellIndex == -1) break;

        index = Int.cellIndex;

        //if (Int.dx != 0)
        //{
        //    cout << index << '\t' << Int.dx << '\t' << Polygon.size() << endl;

        //    while (1)
        //    {
        //        double l = 0;
        //        std::cin >> l;
        //        if (l == 1)
        //            break;
        //    }
        //}

        if (Int.x == Polygon[index].x && Int.y == Polygon[index].dy) continue;

        insertVertex(Int, index);

        int ncanc = (int)Int.dx - index;

        // Qua la cosa diventa difficile, 
        // in pratica se per sfiga becco che uno dei primi
        // segmenti incrocia uno degli ultimi a lui non frega niente e
        // taglia tutto il poligono. Per cui se gli esce che il numero di 
        // roba da tagliare è più della metà taglio al contrario.
        // Quindi elimino partendo dall'ultimo in fondo e vado avanti
        if (Int.dx - index > Polygon.size() / 2)
        {
            ncanc = ((int)Polygon.size() - (int)Int.dx) + index;
            int temp = (int)Int.dx;
            Int.dx = index;
            index = temp - 1;
        }

        for (int j = 0; j != ncanc; j++)
        {
            DeleteVertex(index + 1);
        }

        // Forest->timeHeap.deleteValue(Polygon[index+1].nextTime);
        // Forest->timeHeap.deleteValue(Polygon[index-1].nextTime);
        // calcVelocity(index+1);
        // calcTime(index+1);
        // calcVelocity(index-1);
        // calcTime(index-1);
 
        // Polygon[index].cellIndex = Forest->findCell(Polygon[index]);
        // calcVelocity(index);
        // calcTime(index);
    }
}


void Fire::checkBorder()
{
    for (int i = 0; i < Polygon.size(); i++)
    {

        if(Polygon[i].cellIndex != -1 || Polygon[i+1].cellIndex != -1 || Polygon[i+2].cellIndex != -1)
        {
            continue;
        }

        double min, max;
        Vertex ris1, ris2;

        if (Polygon[i].x == Polygon[i + 1].x && Polygon[i].x == Polygon[i + 2].x)/* ||
             (Polygon[i].x <= 0 && Polygon[i+1].x <= 0 && Polygon[i+2].x <= 0))*/
        {

            ris1.x = ris2.x = Polygon[i].x /*> 0 ? Polygon[i].x : 0*/;
            min = std::min({ Polygon[i].y , Polygon[i + 1].y , Polygon[i + 2].y });
            max = std::max({ Polygon[i].y , Polygon[i + 1].y , Polygon[i + 2].y });
            
            ris1.y = (ris1.x == 0) ? max : min;
            ris2.y = (ris2.x == 0) ? min : max;


        }
        else if (Polygon[i].y == Polygon[i + 1].y && Polygon[i].y == Polygon[i + 2].y) /*||
                 (Polygon[i].y <= 0 && Polygon[i + 1].y <= 0 && Polygon[i + 2].y <= 0))*/
        {
            ris1.y = ris2.y = Polygon[i].y /*> 0 ? Polygon[i].y : 0*/;
            min = std::min({ Polygon[i].x , Polygon[i + 1].x , Polygon[i + 2].x });
            max = std::max({ Polygon[i].x , Polygon[i + 1].x , Polygon[i + 2].x });

            ris1.x = (ris1.y == 0) ? min : max;
            ris2.x = (ris2.y == 0) ? max : min;
        }
        else continue;

        ris1.cellIndex = ris2.cellIndex = -1;
        ris1.dx = ris1.dy = ris2.dx = ris2.dy = 0;
       
        Polygon[i] = ris1;
        Polygon[i + 2] = ris2;
        Polygon.erase(Polygon.begin() + (i + 1) % Polygon.size());

    }
}

ciclicVector<Vertex> Fire::calcDiff(const ciclicVector<Vertex> & v)
{
    ciclicVector<Vertex> Diff(Polygon.size());

    Diff[0] = (Polygon[(int)Polygon.size() - 1] - Polygon[1])/2;

    for(int i = 1; i != Polygon.size(); i++)
    Diff[i] = (Polygon[i + 1] - Polygon[i - 1])/2;

    return Diff;
}

void Fire::DeleteVertex(int n)
{
    if (n < 0) n = (int)Polygon.size() + n;

    int i = n % Polygon.size();

    // Forest->timeHeap.deleteValue(Polygon[i].nextTime);
    Polygon.erase(Polygon.begin() + i);
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