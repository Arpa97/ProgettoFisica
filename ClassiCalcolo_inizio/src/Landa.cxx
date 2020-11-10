# include "Landa.hxx"

# include "Definizioni.hxx"

# include <iostream>
# include <iomanip>
# include <stdlib.h>
# include <time.h>
# include <cmath>

using std::cout;
using std::endl;

//-------------Costruttori-----------

Landa::Landa(int nr, int nc, double T): Nr(nr), Nc(nc)
{
    srand(time(NULL));

    Terreno = new Fuel**[Nr];

    for(int i = 0; i != Nr; i++)
    {
        Terreno[i] = new Fuel*[Nc];

        for(int j = 0; j != Nc; j++)
        {
            Terreno[i][j] = new Fuel(T);
        }
    }
}

//-------------Metodi----------------

void Landa::step(double dt)
{

    // Calcolo termini di radiazione

    double R[Nr][Nc];

    auto f = [](double T)
    {
        return p*Rstar*std::pow(T, 4);
    };

    for(int i = 0; i != Nr; i++)
    for(int j = 0; j != Nc; j++)
    {
        R[i][j] = 0;

        if(Terreno[i][j]->T > Ti)
        continue;

        if(i != 0) if(Terreno[i - 1][j]->T > Ti)
        R[i][j] += f(Terreno[i - 1][j]->T);

        if(i != Nr - 1) if(Terreno[i + 1][j]->T > Ti)
        R[i][j] += f(Terreno[i + 1][j]->T);

        if(j != 0) if(Terreno[i][j - 1]->T > Ti)
        R[i][j] += f(Terreno[i][j - 1]->T);

        if(j != Nc - 1) if(Terreno[i][j + 1]->T > Ti)
        R[i][j] += f(Terreno[i][j + 1]->T);
    }

    //----------------Bilancio termico--------------


    for(int i = 0; i != Nr; i++)
    for(int j = 0; j != Nc; j++)
    {
        double T = Terreno[i][j]->T;
        Terreno[i][j]->eqBilancio(t, R[i][j], dt);

        // Controllo se hanno preso fuoco
        if(Terreno[i][j]->T > Ti && T < Ti)
        Terreno[i][j] = new BurningFuel(Terreno[i][j]->T, Terreno[i][j]->D, Terreno[i][j]->H, t);
    }


    t += dt;
}

void Landa::genDislivello(int nR, int nC, double hMax, double Largh)
{
    // Prendo come x e y  il calore centralle della cella, ecco perché lo 0.5
    double x0 = LCELLE * (0.5 + nR);
    double y0 = LCELLE * (0.5 + nC);

    // Creo la funzione, che poi è una gaussiana
    auto f = [x0, y0, Largh, hMax](double x, double y)
    {
        double r = hMax*std::exp(-std::pow(x - x0, 2)/Largh/Largh)*std::exp(-1*std::pow(y - y0, 2)/Largh/Largh);

        return r < 0.01 ? 0 : r;
    };

    // Setto i valori
    for(int i = 0; i != Nr; i++)
    for(int j = 0; j != Nc; j++)
    Terreno[i][j]->H += f(LCELLE * (0.5 + i), LCELLE * (0.5 + j));
}

void Landa::incRand()
{
    int i = rand() % Nr;
    int j = rand() % Nc;

    while(Terreno[i][j]->T > Ti)
    {
        int i = rand() % Nr;
        int j = rand() % Nc;
    }

    Terreno[i][j] = new BurningFuel(Ti, Terreno[i][j]->D, Terreno[i][j]->H, t);
}





//--------------Altro----------------

void VisualizzaGrigliaT(const Landa & L)
{
    cout << std::setprecision(3);

    const char * colore;

    for(int i = 0; i != L.Nr; i++)
    {
        for(int j = 0; j != L.Nc; j++)
        {
            colore = L.Terreno[i][j]->T < Ti ? "\033[32m" : "\033[31m";

            cout << colore << std::setw(10) << L.Terreno[i][j]->T; 
        }
    
        cout << endl;
    }
}


void VisualizzaGrigliaH(const Landa & L)
{
    cout << std::setprecision(3);

    const char * colore;

    for(int i = 0; i != L.Nr; i++)
    {
        for(int j = 0; j != L.Nc; j++)
        {
            colore = L.Terreno[i][j]->H < 0.01 ? "\033[32m" : "\033[1m\033[34m";

            cout << colore << std::setw(10) << L.Terreno[i][j]->H; 
        }
    
        cout << endl;
    }
}