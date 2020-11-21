/*****************************************************************************************************
* A fuel is the source of heat that sustains the combustion process. It include
* all the combustible plant-derived material including grass, litter, duff, etc..
* Refer to Rothermel.hxx for variable definitions.
*
 *****************************************************************************************************/

#pragma once
#include "Definitions.hxx"

struct Fuel
{
	int fuelIndex;

	const double h = 8;
	const double S_T = 0.0555;
	const double S_e = 0.010;
	const double rho_p = 32;

	const double w_0;
	const double SAV;
	const double delta;
	const double M_x;

	//Reduced rate of speed, calculated only via fuel parameters and moisture content. 
	double R0;

	//-----------Constructors-------------
	Fuel(int _fuelIndex, double _w_0, double _SAV, double _delta, double _M_x) : fuelIndex(_fuelIndex), w_0(_w_0), SAV(_SAV), delta (_delta), M_x(_M_x) {}

	//-----------Methods-------------
	//Compute R0 (reduced R, cannot change run-time) given the moisture content and the fuel proprieties.
	void setR0(double M_f);

	double getWindFactor(double U);
	double getSlopeFactor(double tan_phi);

	//Nota: li ho chiamati set e get ma so che non sono veramente dei setters/getters. Suggerimenti di nomi migliori sono ben accetti
};