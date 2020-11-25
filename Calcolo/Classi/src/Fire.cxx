#include "Fire.hxx"
#include "Environment.hxx"

#include <cmath>

Fire::Fire(Environment * Forest, double Xi, double Yi): Forest(Forest)
{
    Polygon.resize(10);
    
    // Creation of a little ellipse centered on the point roted by
    // the direction of the wind

    Cell * cell = Forest->getCell(Vertex(Xi, Yi));
    double tetha = Forest->getTheta();

    // Support variable for the rotation
    double x1, y1;

    for(int i = 0; i != 10; i++)
    {
        // Divided by 100 because the initial ellipse is needed to be small
        Polygon[i].x = cell->a * std::cos(i*M_PI/5)/100;
        Polygon[i].y = cell->b * std::sin(i*M_PI/5)/100;

        x1 = Polygon[i].x * std::cos(tetha) + Polygon[i].y * std::sin(tetha);
        y1 = Polygon[i].y * std::cos(tetha) - Polygon[i].x * std::sin(tetha);

        Polygon[i].x = Xi + x1;
        Polygon[i].y = Yi + y1;
    }
}

Fire::Fire(const Fire & f): Forest(f.Forest)
{
    for(int i = 0; i != Polygon.size(); i++)
    Polygon.push_back(f.Polygon[i]);
}



// ----------------Methods-------------------

void Fire::Propagate(double dt)
{
    // Checking distance from verteces
    checkDistance();

    double par[3];
    double tetha = Forest->getTheta();
    ciclicVector<Vertex> Diff = calcDiff(Polygon);
    
    double Ct = std::cos(tetha), St = std::sin(tetha);

    double At, Bt, num1, num2, den;

    for(int i = 0; i != Polygon.size(); i++)
    {
    	getParam(par, i);
    	
        // Computing the vertex differential for propagating the front
        At = par[0] * (Diff[i].x * St + Diff[i].y * Ct);
        Bt = par[1] * (Diff[i].y * St - Diff[i].x * Ct);

        num1 = par[0] * At * Ct + par[1] * Bt * St;
        num2 = par[1] * Bt * Ct - par[0] * At * St;

        den = std::sqrt(At*At + Bt*Bt);

        Polygon[i].x += (num1/den + par[2] * St)*dt;
        Polygon[i].y += (num2/den + par[2] * Ct)*dt;
    }
}

void Fire::calcPropagation(double * val, int i)
{
    double par[3];
    getParam(par, i);

    double At, Bt, num1, num2, den;
    double Ct = std::cos(Forest->getTheta());
    double St = std::sin(Forest->getTheta());
    Vertex Diff = (Polygon[i + 1] - Polygon[i - 1])/2; 

    At = par[0] * (Diff.x * St + Diff.y * Ct);
    Bt = par[1] * (Diff.y * St - Diff.x * Ct);

    num1 = par[0] * At * Ct + par[1] * Bt * St;
    num2 = par[1] * Bt * Ct - par[0] * At * St;

    den = std::sqrt(At*At + Bt*Bt);

    val[0] =  num1/den + par[2] * St;
    val[1] =  num2/den + par[2] * Ct;
}

void Fire::getParam(double * par, int i)
{
    // Da scrivere una volta che ho tutti i parametri

    Cell * cella = Forest->getCell(Polygon[i]);

    par[0] = cella->a;
    par[1] = cella->b;
    par[2] = cella->c;
}


ciclicVector<Vertex> Fire::calcDiff(const ciclicVector<Vertex> & v)
{
    ciclicVector<Vertex> Diff(Polygon.size());

    Diff[0] = (Polygon[Polygon.size() - 1] - Polygon[1])/2;

    for(int i = 1; i != Polygon.size(); i++)
    Diff[i] = (Polygon[i + 1] - Polygon[i - 1])/2;

    return Diff;
}
