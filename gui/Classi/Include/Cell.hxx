/*********************************************************************
 *
 * Class that represent a single cell of fuel in the grid.
 * 
 *
 *********************************************************************/


#pragma once

#include "Vertex.hxx"
#include "Fuel.hxx"
#include "Definitions.hxx"

struct Cell 
{
	int fuelIndex, fuelNumber;
	double height;
	double slope[2];

	// Parameters for the advance method
	double R, maxTheta;
	double a, b, c;

	// The +1 is for counting the ground with R = 0
	static Fuel* FuelType[N_FUEL_TYPES + 1];				
	//Nota: si potrebbe anche rendere un vector e fare uno static AddFuelType, ma non credo abbiamo interesse di aggiungere Fuel personalizzati.

	//-----------Constructors-------------
	Cell(int _fuelNumber, double _height = 0);
	Cell(Cell& c);

	//-----------Methods-------------
	static void FillFuelType(double M_f);
	void setR(double U, double theta = 0);
	void updateEllipseParams(double U);

};