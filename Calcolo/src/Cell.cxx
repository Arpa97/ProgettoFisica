#include "Rothermel.hxx"
#include "Cell.hxx"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

Fuel* Cell::FuelType[N_FUEL_TYPES];


void Cell::FillFuelType(double M_f)
{
	std::ifstream fcin;
	fcin.open(FUEL_PATH);
	if (fcin.fail())	throw;
	
	double w_0, SAV, delta, M_x;
	int fuelIndex;

	fcin.ignore(1000, '\n');
	for (int i = 0; i != N_FUEL_TYPES; i++)
	{
		fcin.ignore(10, '\t');
		fcin >> fuelIndex;
		fcin.ignore(10, '\t');
		fcin.ignore(10, '\t');
		fcin >> w_0;
		w_0 /= 21.78;						//Conversion: 1 ft/m2 = 21.78 ton/acre
		fcin.ignore(10, '\t');
		fcin.ignore(10, '\t');
		fcin.ignore(10, '\t');
		fcin.ignore(10, '\t');
		fcin.ignore(10, '\t');
		fcin >> SAV;
		fcin.ignore(10, '\t');
		fcin.ignore(10, '\t');
		fcin.ignore(10, '\t');
		fcin >> delta;
		fcin >> M_x;
		M_x /= 100;

		FuelType[i] = new Fuel(w_0, SAV,  delta, M_x);
		FuelType[i]->setR0(M_f);
	}
}



void Cell::setR(double U)
{
	double R0 = FuelType[fuelIndex - 1]->R0;
	double phi_w = FuelType[fuelIndex - 1]->getWindFactor(U);
	R = Rothermel_R(R0, phi_w);
	R *= 0.00508;							//Conversion: 1 ft/min = 0.00508 m/s
	updateEllipseParams(U);
}

void Cell::updateEllipseParams(double U)
{
	double LB = 0.936 * exp(0.2566 * U) + 0.461 * exp(-0.1548 * U) - 0.397;
	double HB = (LB + sqrt(LB * LB - 1)) / (LB - sqrt(LB * LB - 1));
	a = R * (1 + 1 / HB) / (2 * LB);
	b = R * (1 + 1 / HB) / 2;
	c = b - R / HB;
}
