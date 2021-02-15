/*****************************************************************************************************
* A fuel is the source of heat that sustains the combustion process. It include
* all the combustible plant-derived material including grass, litter, duff, etc..
* Refer to Rothermel.hxx for variable definitions.
*
 *****************************************************************************************************/

#pragma once

#include "Definitions.hxx"
#include <vector>

struct Fuel
{
	// Definiti static in modo tale da non occupare memoria in più
	// e nel caso danno la possibilità di usarli anche senza un istanza della classe
	static constexpr double h = 8000;
	static constexpr double S_T = 0.0555;
	static constexpr double S_e = 0.010;
	static constexpr double rho_p = 32;

	std::vector<double>* w_0;
	const std::vector<double>* SAV;
	const double delta;
	const double M_x;

	//Reduced rate of spread, calculated only via fuel parameters and moisture content. 
	double R0;

	//-----------Constructors-------------
	Fuel(std::vector<double>* _w_0, std::vector<double>* _SAV, double _delta, double _M_x) : w_0(_w_0), SAV(_SAV), delta (_delta), M_x(_M_x) {}

	//-----------Methods-------------
	//Compute R0 (reduced R, cannot change run-time) given the moisture content and the fuel proprieties.
	void setR0(double M_f);

	double getWindFactor(double U);
	double getSlopeFactor(double tan_phi);

	//Nota: li ho chiamati set e get ma so che non sono veramente dei setters/getters. Suggerimenti di nomi migliori sono ben accetti
};