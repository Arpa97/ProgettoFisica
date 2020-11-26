#include "Environment.hxx"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip> 

using std::cout;
using std::endl;

Environment::Environment(double (*fuelPercentages)[2], int nDifferentFuels)
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
		grid[i] = i != step - 1 ? new Cell * [step] : new Cell * [step + 1];

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

	// Adding the fuel of type 0 at the end
	grid[step-1][step] = new Cell(0, 0);
}



void Environment::advance(double dt)
{
	double dt1, nextTime;
	double tfinale = time + dt - 0.00001;

	while(time < tfinale)
	{
		// Searching the next timestep
		nextTime = timeHeap.top();
		// timeHeap.pop();
		dt1 = nextTime - time;
		time += dt1;

		if(time > tfinale)
		{
			dt1 += tfinale - time;
			time = tfinale;
		}
		else
		timeHeap.pop();

		// propagation of the fire
		for (int i = 0; i != wildfire.size(); i++)
		wildfire[i]->Propagate(dt1);
	}

	std::cerr << "Time : " << time << '\n';
}



Cell* Environment::getCell(int cellIndex)
{
	int step = GRID_SIDE / CELL_SIDE;
	int j = cellIndex % step;
	int i = (cellIndex - j) / step;
	return grid[i][j];
}


Cell* Environment::getCell(double x, double y)
{
	return getCell(findCell(x, y));
}


Cell * Environment::getCell(const Vertex & v)
{
	return getCell(findCell(v));
}



int Environment::findCell(double x, double y) const
{
	int step = GRID_SIDE / CELL_SIDE;

	// Returning the fuel of type 0 if the vertex croos the forest
	if (x > GRID_SIDE || y > GRID_SIDE || x < 0 || y < 0) step*step;		

	int i = static_cast<int>(y / CELL_SIDE);
	int j = static_cast<int>(x / CELL_SIDE);

	int cellIndex = step * i + j;
	return cellIndex;
}



int Environment::findCell(const Vertex& v) const
{
	return findCell(v.x, v.y);
}



void Environment::addFire(double Xi, double Yi)
{
	wildfire.push_back(
		new Fire(this, Xi, Yi)
	);
}



void Environment::setU(double _U)
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

double Environment::getU() const
{
	return U;
}

double Environment::getTheta() const
{
	return theta;
}

double Environment::getM_f() const
{
	return M_f;
}


ciclicVector<Vertex> Environment::getPolygon(int i)
{
	return wildfire[i]->Polygon;
}


void Environment::VisualizeGrid()
{
	int step = GRID_SIDE/CELL_SIDE;

	for(int i = 0; i != step; i++)
	for(int j = 0; j != step; j++)
	if(j != step - 1)
	cout << grid[i][j]->fuelIndex;
	else 
	cout << grid[i][j]->fuelIndex << endl; 

}