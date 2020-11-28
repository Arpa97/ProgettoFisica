/*********************************************************************
 *
 * Class that represent a single cell of fuel in the grid.
 * 
 *
 *********************************************************************/


#pragma once

#include "Fuel.hxx"
#include "Definitions.hxx"

struct Cell 
{
	int fuelIndex;
	double height;

	double R;
	double a, b, c;

	// The +1 is for counting the ground with R = 0
	static Fuel* FuelType[N_FUEL_TYPES + 1];				
	//Nota: si potrebbe anche rendere un vector e fare uno static AddFuelType, ma non credo abbiamo interesse di aggiungere Fuel personalizzati.
	//Nota2: per far corrispondere i fuelIndex con gli indici dei fuel standard, occorre chiamare FuelType[fuelIndex - 1].
	//Si potrebbe cambiare la cosa facendo un array grande N_FUEL_TYPES + 1 e istanziando all'indice 0 un Fuel non usato.

	//-----------Constructors-------------
	Cell(int _fuelIndex, double _height = 0) : fuelIndex(_fuelIndex), height(_height) {}


	//-----------Methods-------------
	static void FillFuelType(double M_f);
	void setR(double U);
	void updateEllipseParams(double U);

};