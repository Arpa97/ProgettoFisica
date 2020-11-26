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
#include <queue>
#include <functional>

class Environment
{
	double U;
	//Nota: volutamente privati, in modo che non si possa modificare direttamente U ma lo si possa fare
	//solo attraverso il setter, che aggiorna anche il valore di R per ogni cella.
	double theta;
	double M_f;

public:

	double time = 0;
	Cell*** grid;
	std::vector<Fire*> wildfire;
	std::priority_queue<double, std::vector<double>, std::greater<double>> timeHeap;


	//Constructor that creates a grid based on an array of couples fuelIndex-fuelPercentage (sum of all percentages must be 1)
	//Nota: bozza eventualmente da buttare a seconda di come si deciderà gestire la variabilità dei fuel, 
	//e può essere reso un std::array in modo da contenere l'informazione sulla size 
	//Nota2: Andrà modificato per ricevere dalla GUI anche vento, direzione e umidità	
	Environment(double (*fuelPercentages)[2] = nullptr, int nDifferentFuels = 0);

	//---------------Methods----------------
	void advance(double dt);

	Cell* getCell(int cellIndex);
	Cell* getCell(double x, double y);
	Cell* getCell(const Vertex & v);
	int findCell(double x, double y) const;
	int findCell(const Vertex& v) const;

	// Used to add a fire in a specific point defined by xi e yi
	void addFire(double Xi, double Yi);

	void setU(double _U);
	double getU() const;
	double getTheta() const;
	double getM_f() const;

	// Methods for getting the polygon of a specific fire in the index i
	ciclicVector<Vertex> getPolygon(int i);

	//Method to visualize the grid
	void VisualizeGrid();
};