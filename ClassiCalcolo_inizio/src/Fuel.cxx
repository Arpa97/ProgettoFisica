# include "Fuel.hxx"

# include "Definizioni.hxx"

//-------------Costruttori-----------

Fuel::Fuel(double T, double D, double H): T(T), H(H), D(D) {}



Fuel::Fuel(const Fuel & c): T(c.T), D(c.D), H(c.H) {}


//-------------Metodi---------------

void Fuel::eqBilancio(double t, double R, double dt)
{
    // Dichiaro un functor per fare i calcoli in maniera da non impazzire
    auto f = [R](double T)
    {
        return -K*(T - Ta) + R;
    };


    // Runge-Koutta quarto ordine

    double k1 = f(T);
    double k2 = f(T + k1*dt/2);
    double k3 = f(T + k2*dt/2);
    double k4 = f(T + k3*dt);

    T += dt*(k1 + 2*k2 + 2*k3 + k4)/6;
}
