/************************************
 * 
 * Classe per fare che conterrà la griglia
 * di Fuel che rappresenta il terreno.
 * 
 */

# pragma once

#include "BurningFuel.hxx"


struct Landa
{
    //-------------Attributi-------------

    // Variabile temporale
    double t = 0;

    // Numero di righe e colonne della griglia
    int Nr;
    int Nc;

    // Griglia con tutti i dati
    Fuel *** Terreno;

    //-------------Costruttori-----------

    Landa(int nr, int nc, double T = 300);

    //-------------Metodi----------------

    // Metodo per andare avanti nel tempo
    void step(double dt = 0.01);

    // Metodo per generare un dislivello in una zona
    void genDislivello(int nR, int nC, double hMax, double Largh = 1);

    // Metodo per appiccare un incendio in pos rand
    void incRand();
};




// Funzione per la visualizzazione dei valori
void VisualizzaGrigliaT(const Landa & L);
void VisualizzaGrigliaH(const Landa & L);