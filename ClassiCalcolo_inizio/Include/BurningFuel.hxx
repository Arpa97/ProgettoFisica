/*******************************
 * 
 * Classe derivata da Fuel, 
 * rappresenta una cella che 
 * brucia.
 * 
 * In pratica devo ridefinire 
 * l'equazione di bilancio per 
 * aggiungere la combustione 
 * 
 */


# pragma once


# include "Fuel.hxx"
# include "Definizioni.hxx"


struct BurningFuel : public Fuel
{
    //-------------Attributi-------------

    // Momento in cui ha iniziato a prendere fuoco
    double ti;

    //-------------Costruttori-----------
    
    BurningFuel(double T = Ti, double D = 1, double H = 0, double ti = 0);
    BurningFuel(const Fuel & c, double ti);
    BurningFuel(const BurningFuel & c);

    //-------------Metodi----------------

    void eqBilancio(double t, double R, double dt);
};
