# include "Fire.hxx"

# include <cmath>


// ----------------Metods-------------------

void Fire::Propagate(double dt)
{
    // Checking distance from verteces
    checkDistance();

    double par[4];
    double tetha = Forest->tetha;
    ciclicVector<Vertex> Diff = calcDiff(Polygon);
    
    double Ct = std::cos(tetha), St = std::sin(tetha);

    double At, Bt, num1, num2, den;

    for(int i = 0; i != Polygon.size(); i++)
    {
        // Computing the vertex differential for propagating the front
        At = par[0] * (Diff[i].x * St + Diff[i].y * Ct);
        Bt = par[1] * (Diff[i].y * St - Diff[i].x * Ct);

        num1 = par[0] * At * Ct + par[1] * Bt * St;
        num2 = par[1] * Bt * Ct - par[0] * At * St;

        den = std::sqrt(At*At + Bt*Bt);

        Polygon[i].x += (num1/den + par[3] * St)*dt;
        Polygon[i].y += (num2/den + par[3] * Ct)*dt;
    }
}

void Fire::getParam(double * par, int i)
{
    // Da scrivere una volta che ho tutti i parametri
}


ciclicVector<Vertex> Fire::calcDiff(const ciclicVector<Vertex> & v)
{
    ciclicVector<Vertex> Diff(Polygon.size());

    for(int i = 0; i != Polygon.size(); i++)
    Diff[i] = (Polygon[i + 1] - Polygon[i - 1])/2;

    return Diff;
}