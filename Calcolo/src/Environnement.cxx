#include "Environnement.hxx"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

Environnement::Environnement(double (*fuelPercentages)[2], int nDifferentFuels)
{
	U = WIND_SPEED;
	theta = WIND_DIRECTION;
	M_f = MOISTURE_CONTENT;
	Cell::FillFuelType(M_f);

	int step = GRID_SIDE / CELL_SIDE;	
	int fuelNumber, number;
	double validator;
	srand(static_cast<unsigned int>(std::time(NULL)));

	grid = new Cell * *[step];

	for (int i = 0; i != step; i++)
	{
		grid[i] = new Cell * [step];

		for (int j = 0; j != step; j++)
		{
			if (fuelPercentages == nullptr) fuelNumber = 1;
			else do
			{
				number = rand() % nDifferentFuels;
				fuelNumber = (int)fuelPercentages[number][0];
				validator = rand() / (RAND_MAX + 0.0);

			} while (validator > fuelPercentages[number][1]);

			grid[i][j] = new Cell(fuelNumber, 0);
			grid[i][j]->setR(U);
		}
	}
}



void Environnement::advance()
{
	for (int i = 0; i != wildfire.size(); i++)
	{
		wildfire[i]->Propagate(TIMESTEP);
	}
	time += TIMESTEP;
}



Cell * Environnement::getCell(const Vertex & v)
{
	int cellIndex = findCell(v.x, v.y);
	int step = GRID_SIDE / CELL_SIDE;
	int j = cellIndex % step;
	int i = (cellIndex - j) / step;
	return grid[i][j];
}



Cell* Environnement::getCell(int cellIndex)
{
	int step = GRID_SIDE / CELL_SIDE;
	int j = cellIndex % step;
	int i = (cellIndex - j) / step;
	return grid[i][j];
}



int Environnement::findCell(double x, double y) const
{
	if (x > GRID_SIDE || y > GRID_SIDE) throw;		//Nota: cosa succede quando un vertice esce dalla griglia? occorrer� capire come gestire la cosa
	int step = GRID_SIDE / CELL_SIDE;

	int i = static_cast<int>(y / CELL_SIDE);
	int j = static_cast<int>(x / CELL_SIDE);

	int cellIndex = step * i + j;
	return cellIndex;
}



void Environnement::addFire(double Xi, double Yi)
{
	wildfire.push_back(
		new Fire(this, Xi, Yi)
	);
}



void Environnement::setU(double _U)
{
	U = _U;
	int step = GRID_SIDE / CELL_SIDE;
	for (int i = 0; i != step; i++)
	{
		for (int j = 0; j != step; j++)
		{
			grid[i][j]->setR(U);
		}
	}
}

double Environnement::getU() const
{
	return U;
}

double Environnement::getTheta() const
{
	return theta;
}

double Environnement::getM_f() const
{
	return M_f;
}