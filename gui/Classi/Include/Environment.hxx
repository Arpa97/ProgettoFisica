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
#include "PriorityQueue.hxx"

#include <functional>

class Environment
{
	double U;
	//Nota: volutamente privati, in modo che non si possa modificare direttamente U ma lo si possa fare
	//solo attraverso il setter, che aggiorna anche il valore di R per ogni cella.
	double theta;
	double M_f;

	// Methods for inizializing the times and the factor in the vertices
	void calcAll();

public:

	double time = 0;
	Cell*** grid;
	static Cell* nullFuel;
	std::vector<Fire*> wildfire;
	PriorityQueue timeHeap;


	//Constructor that creates a grid based on an array of couples fuelIndex-fuelPercentage (sum of all percentages must be 1)
    Environment(const std::vector<std::vector<double>>& fuelPercentages, double moistureContent);

	//---------------Methods----------------
	
	//Advance the system of a specified timestep, or if not specified until the first vertex in Polygon changes cell.
	void advance(double dt);
	void advance();
	void advance_withoutHeap();

	Cell* getCell(int cellIndex);
	Cell* getCell(double x, double y);
	Cell* getCell(Vertex & v);
	int findCell(double& x, double& y);
	int findCell(Vertex& v);

	// Used to add a fire in a specific point defined by xi e yi
	void addFire(double Xi, double Yi);

	// Methods for the wind setting and getting
	void setU(double _U);
	void setTheta(double _theta);
	void setMf(double _Mf);
	double getU() const;
	double getTheta() const;
	double getM_f() const;

	// Method to set the type of a cell
    void setCellType(double &x, double &y, int fNumber);

    // Method for height computing
	void addMountain(double h, double pos[2], double lar);

	// Methods for getting the polygon of a specific fire in the index i
	ciclicVector<Vertex> getPolygon(int i);

	double getBurnedArea();

	//Method to visualize the grid
	void VisualizeGrid();

	//Method to get the fuels information
	//Questo array di puntatori a fuel ha dimensione N_FUEL_TYPES + 1 e il valore storato a [0] è il tipo nullo
	//il quale NON deve essere messo nelle scelte possibili con cui disegnare la mappa
	//Per prendere il nome di un fuel basta quindi fare Environment::getFuelInfo()[i]->name;
    static std::vector<Fuel*> getFuelInfo();

    // Get maximum moisture for this forest
    double getMaximumMoisture();
};
