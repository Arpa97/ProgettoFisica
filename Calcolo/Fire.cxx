# include "Fire.hxx"
# include "Environnement.hxx"

# include <cmath>


// ----------------Methods-------------------

void Fire::Propagate(double dt)
{
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
    // Checking distance from verteces
    checkDistance();
}

void Fire::getParam(double * par, int i)
{
    // Da scrivere una volta che ho tutti i parametri
}


ciclicVector<Vertex> Fire::calcDiff(const ciclicVector<Vertex> & v)
{
    ciclicVector<Vertex> Diff(Polygon.size());

    Diff[0] = (Polygon[Polygon.size() - 1] - Polygon[1])/2;

    for(int i = 1; i != Polygon.size(); i++)
    Diff[i] = (Polygon[i + 1] - Polygon[i - 1])/2;

    return Diff;
}
