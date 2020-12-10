#include "Environment.hxx"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip> 

using std::cout;
using std::endl;

Cell* Environment::nullFuel = new Cell(0, 0);

Environment::Environment(double (*fuelPercentages)[2], int nDifferentFuels)
{
	U = 0;
	theta = 0;
	M_f = MOISTURE_CONTENT;
	Cell::FillFuelType(M_f);
	nullFuel->setR(0);

	int step = GRID_SIDE / CELL_SIDE;	
	int fuelNumber, number;
	double validator;
	//srand(static_cast<unsigned int>(std::time(NULL)));

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



void Environment::advance(double dt)
{
	double dtHeap, dtMin, nextTime;
	double tfinale = time + dt;
	int numero = 0;

	//std::cerr << "[";
	while(time < tfinale)
	{
		numero++;
		// Searching the next timestep
		nextTime = timeHeap.top();
		dtHeap = nextTime - time;
		dt = tfinale - time;

		if (dtHeap < dt)
		{
			dtMin = dtHeap;
			timeHeap.pop();
		}
		else dtMin = dt;

		time += dtMin;

		// propagation of the fire
		for (int i = 0; i != wildfire.size(); i++)
		{
			wildfire[i]->Propagate(dtMin);
		}

		for(int i = 0; i != wildfire.size(); i++)
		wildfire[i]->checkEdges();

		calcTimes();		
	}
	//std::cerr << '\n';
	//std::cout << "Time : " << time << '\t' << "Avanzamenti: " << numero << "\tNumero punti:" << wildfire[0]->Polygon.size() << '\n';
}



void Environment::advance()
{
	double nextTime = timeHeap.top();
	timeHeap.pop();
	double dt = nextTime - time;
	time += dt;

	for (int i = 0; i != wildfire.size(); i++)
	{
		wildfire[i]->Propagate(dt);
	}

	std::cerr << "Time : " << time << '\n';
}

void Environment::advance_withoutHeap()
{
	double dt = 1;
	time += dt;

	for (int i = 0; i != wildfire.size(); i++)
	{
		wildfire[i]->Propagate_withoutHeap(dt);
	}

	//std::cerr << "Time : " << time << '\n';

}



Cell* Environment::getCell(int cellIndex)
{
	if (cellIndex == -1)
	{
		return nullFuel;
	}

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
	// Returning the fuel of type 0 if the vertex croos the forest
	if (x >= GRID_SIDE || y >= GRID_SIDE || x < 0 || y < 0) return -1;		

	int step = GRID_SIDE / CELL_SIDE;

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

	// Recalculate all timesteps
	calcTimes();
}

void Environment::setTheta(double _theta){
	theta = _theta;

	// Recalculate all timesteps
	calcTimes();
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


void Environment::calcTimes()
{
	// First calcel all the old entries
	while (!timeHeap.empty())
	timeHeap.pop();
	
	// Recalculate all propagation for all vertices
	for(int i = 0; i != wildfire.size(); i++)
	wildfire[i]->calcPropagations();

	// Recalculate the times for all vertices
	for(int i = 0; i != wildfire.size(); i++)
	wildfire[i]->calcTimes();
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