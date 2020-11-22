/*****************************************************************************************************
*
* General class corresponding to the forest. Contains the cell grid and manages the 
* timestep for fire propagation. 
*
 *****************************************************************************************************/


#pragma once

#include "Definitions.hxx"
#include "Cell.hxx"
#include "Fire.hxx"

#include <vector>

class Environnement
{
	double U;
	//Nota: volutamente privati, in modo che non si possa modificare direttamente U ma lo si possa fare
	//solo attraverso il setter, che aggiorna anche il valore di R per ogni cella.
	double theta;
	double M_f;

public:

	Cell*** grid;
	std::vector<Fire*> wildfire;
	double time;

	//Constructor that creates a grid based on an array of couples fuelIndex-fuelPercentage (sum of all percentages must be 1)
	//Nota: bozza eventualmente da buttare a seconda di come si decider� gestire la variabilit� dei fuel, 
	//e pu� essere reso un std::array in modo da contenere l'informazione sulla size 
	//Nota2: Andr� modificato per ricevere dalla GUI anche vento, direzione e umidit�	
	Environnement(double (*fuelPercentages)[2] = nullptr, int nDifferentFuels = 0);

	//---------------Methods----------------
	void advance();

	Cell* getCell(int cellIndex);
	int findCell(double x, double y) const;

	void addFire(Fire* fire);

	void setU(double _U);
	double getU() const;
	double getTheta() const;
	double getM_f() const;
};