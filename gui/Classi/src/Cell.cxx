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
	fuelIndex = numberToIndex(fuelNumber);
	slope[0] = 0;
	slope[1] = 0;
}

Cell::Cell(Cell& c)
{
	fuelIndex = c.fuelIndex;
	fuelNumber = c.fuelNumber;
	height = c.height;
	R = c.R;
	a = c.a;
	b = c.b;
	slope[0] = c.slope[0];
	slope[1] = c.slope[1];
	this->c = c.c;
}

int Cell::numberToIndex(int fuelNumber)
{
	int fIndex;

	if (fuelNumber < 100)
	{
		fIndex = fuelNumber;
	}
	else if (fuelNumber < 110)
	{
		fIndex = fuelNumber - 88;
	}
	else if (fuelNumber < 125)
	{
		fIndex = fuelNumber - 99;
	}
	else if (fuelNumber < 150)
	{
		fIndex = fuelNumber - 115;
	}
	else if (fuelNumber < 170)
	{
		fIndex = fuelNumber - 126;
	}
	else if (fuelNumber < 190)
	{
		fIndex = fuelNumber - 141;
	}
	else
	{
		fIndex = fuelNumber - 152;
	}
	return fIndex;
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


        fcin.get(); // To remove the space char before the next line, cleaning the name (i.e. " Timber Glass" becomes "Timber Glass")
        getline(fcin, FuelType[i]->name, '\n');
	}

	// Adding the fuel of type 0
	FuelType[0] = new Fuel({}, {}, 0, 0, 'S');
	FuelType[0]->R0 = 0;
	FuelType[0]->name = "Nullo";
}


void Cell::setR(double U, double theta)
{
	if (fuelIndex == 0)
	{
		R = 0;
		return;
	}

	// Putting the wind angle in the direction where it came for convention
	theta += M_PI;
	
	if (WIND_LIMIT)
	{
		if (U > FuelType[fuelIndex]->Umax)
		{
			U = FuelType[fuelIndex]->Umax;
		}
	}
	double Uft = U / 0.00508;

	// Computing max direction
	double R0 = FuelType[fuelIndex]->R0;
	double aspect = std::atan2(slope[0], slope[1]);
	double tanSlo = std::sqrt(slope[0]*slope[0] + slope[1]*slope[1]);
	double E = E = 0.715 * exp(-3.59e-4 * FuelType[fuelIndex]->params[2]);
    double C = 7.47 * exp(-0.133 * pow(FuelType[fuelIndex]->params[2], 0.55))*pow(FuelType[fuelIndex]->params[0] / FuelType[fuelIndex]->params[1], -E);
    double A = 5.275 * pow(FuelType[fuelIndex]->params[0], -0.3);
    double B = 0.02526 * pow(FuelType[fuelIndex]->params[2], 0.54);
	
	double MaxDirX, MaxDirY;

	MaxDirX = C*std::pow(Uft, B)*std::sin(theta - aspect);
    MaxDirY = C*std::pow(Uft, B)*std::cos(theta - aspect) + A*tanSlo*tanSlo;

	// storing the max direction angle and ros
	maxTheta = std::atan2(MaxDirX, MaxDirY) + aspect + M_PI;
	double Uws = std::sqrt(std::pow(MaxDirX, 2) + std::pow(MaxDirY, 2));		//wind speed efficace

	R = R0*(1 + Uws) * 0.00508;

	updateEllipseParams(std::pow(Uws/C, 1/B) * 0.00508);
}

void Cell::updateEllipseParams(double U)
{
	double LB = 0.936 * exp(0.2566 * U) + 0.461 * exp(-0.1548 * U) - 0.397;
	double HB = (LB + sqrt(LB * LB - 1)) / (LB - sqrt(LB * LB - 1));
	a = R * (1 + 1 / HB) / (2 * LB);
	b = R * (1 + 1 / HB) / 2;
	c = b - R / HB;
}
