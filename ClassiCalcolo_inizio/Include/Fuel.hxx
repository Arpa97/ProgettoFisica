/*********************************
 * 
 * Clasee contenitore per i dati 
 * su cui andremo a lavorare.
 * 
 * A livello fisico è un quadratino
 * nella griglia in cui si divide il
 * territorio
 * 
 * ******************************/

# pragma once


struct Fuel
{
    //-------------Attributi-------------

    // Temperatura
    double T;

    // Densità di fuel nel qudratino
    double D;

    // Slope del quadratino
    double H;

    //-------------Costruttori-----------

    Fuel(double T = 300, double D = 1, double H = 0);

    Fuel(const Fuel & c);


    //-------------Metodi----------------

    /*
        Equazione per il bilancio della temperatura 
        interna, ogni tipo di cella ha la sua, inoltre
        serve il momento a cui è stata chiamata.
        Integra anche l'equazione e manda avanti la 
        temperatura. R è il termine delle radiazioni.
    */
    virtual void eqBilancio(double t, double R, double dt = 0.01);
};
