#include "Rothermel.hxx"
#include "Rothermel2.hxx"
#include "Cell.hxx"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;

Fuel* Cell::FuelType[N_FUEL_TYPES + 1];


Cell::Cell(int _fuelNumber, double _height) : fuelNumber(_fuelNumber), height(_height) 
{
	if (fuelNumber < 100)
	{
		fuelIndex = fuelNumber;
	}
	else if (fuelNumber < 110)
	{
		fuelIndex = fuelNumber - 88;
	}
	else if (fuelNumber < 125)
	{
		fuelIndex = fuelNumber - 99;
	}
	else if (fuelNumber < 150)
	{
		fuelIndex = fuelNumber - 115;
	}
	else if (fuelNumber < 170)
	{
		fuelIndex = fuelNumber - 126;
	}
	else if (fuelNumber < 190)
	{
		fuelIndex = fuelNumber - 141;
	}
	else
	{
		fuelIndex = fuelNumber - 152;
	}
}


void Cell::FillFuelType(double M_f)
{
	std::ifstream fcin;
	fcin.open(FUEL_PATH);
	if (fcin.fail())	throw;
	
	char type;
	double delta, M_x;
	int fuelIndex;
	vector<vector<double>> w_0(2);
	vector<vector<double>> SAV(2);
	w_0[0] = vector<double>(4);
	SAV[0] = vector<double>(4);
	w_0[1] = vector<double>(2);
	SAV[1] = vector<double>(2);

	fcin.ignore(1000, '\n');
	for (int i = 1; i != N_FUEL_TYPES + 1; i++)
	{
		fcin.ignore(10, '\t');
		fcin >> fuelIndex;
		fcin.ignore(10, '\t');
		fcin >> type;
		fcin >> w_0[0][0];
		fcin >> w_0[0][1];
		fcin >> w_0[0][2];
		fcin >> w_0[1][0];
		fcin >> w_0[1][1];
		fcin >> SAV[0][0];
		fcin >> SAV[1][0];
		fcin >> SAV[1][1];
		fcin >> delta;
		fcin >> M_x;

		w_0[0][3] = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < w_0[i].size(); j++)
			{
				w_0[i][j] /= 21.78;						//Conversion: 1 ft/m2 = 21.78 ton/acre
			}
		}
		SAV[0][1] = 109;
		SAV[0][2] = 30;
		SAV[0][3] = SAV[1][0];							//live and dead herbaceous SAV is the same
		M_x /= 100;										//Conversion: percentage to fraction

		FuelType[i] = new Fuel(w_0, SAV, delta, M_x, type);
		FuelType[i]->setR0(M_f);
	}

	// Adding the fuel of type 0
	FuelType[0] = new Fuel({}, {}, 0, 0, 'S');
	FuelType[0]->R0 = 0;
}



void Cell::setR(double U)
{
	if (fuelIndex == 0)
	{
		R = 0;
		return;
	}

	double R0 = FuelType[fuelIndex]->R0;
	double phi_w = FuelType[fuelIndex]->getWindFactor(U);
	double phi_s = FuelType[fuelIndex]->getSlopeFactor(
		std::sqrt(AspVect.x*AspVect.x + AspVect.y*AspVect.y)
		);
	
	// if(AspVect.x != 0)
	// cout << "Vettore dell'aspect = (" << AspVect.x << ", " << AspVect.y << ")" << endl;

	if (HETEROGENEOUS_FUEL)
	{
		R = Rothermel2_R(R0, phi_w, phi_s);
	}
	else
	{
		R = Rothermel_R(R0, phi_w, phi_s);
	}
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
