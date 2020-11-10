# include "BurningFuel.hxx"

# include <cmath>
# include <iostream>
# include <iomanip>

using std::cout;
using std::endl;

//-------------Costruttori-----------
    
BurningFuel::BurningFuel(double T, double D, double H, double ti): Fuel(T, D, H), ti(ti) {}


BurningFuel::BurningFuel(const Fuel & c, double ti): Fuel(c), ti(ti) {}


BurningFuel::BurningFuel(const BurningFuel & c): Fuel(c.T, c.D, c.H), ti(ti) {}

//-------------Metodi----------------

void BurningFuel::eqBilancio(double t, double R, double dt)
{
    // Dichiaro un functor per fare i calcoli in maniera da non impazzire
    auto f = [R](double T, double t, double D, double ti)
    {
        return -K*(T - Ta) + D*Q*a*std::exp(-a*(t - ti));
    };


    // Runge-Koutta quarto ordine

    double k1 = f(T, t, D, ti);
    double k2 = f(T + k1*dt/2, t + dt/2, D, ti);
    double k3 = f(T + k2*dt/2, t + dt/2, D, ti);
    double k4 = f(T + k3*dt, t + dt, D, ti);

    T += dt*(k1 + 2*k2 + 2*k3 + k4)/6;

    // cout << endl << dt*(k1 + 2*k2 + 2*k3 + k4)/6 << endl;
}