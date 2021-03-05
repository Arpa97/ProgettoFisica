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
	Fire::setEnvironment(this);

	int step = GRID_SIDE / CELL_SIDE;	
	int fuelNumber, number;
	double validator;
	if (RANDOM)
	{
		srand(static_cast<unsigned int>(std::time(NULL)));
	}

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
			grid[i][j]->setR(U, theta);
		}
	}	
}


void Environment::advance(double dt)
{
	double dtHeap, dtMin, nextTime;
	double tfinale = time + dt;
	int numero = 0;

	while(time < tfinale)
	{
		if (timeHeap.empty())
		{
			wildfire[0]->checkBorder();
			break;
		}

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

		calcAll();		
	}
}



void Environment::advance()
{
	//double nextTime = timeHeap.top();
	//timeHeap.pop();
	//double dt = nextTime - time;
	//time += dt;

	//for (int i = 0; i != wildfire.size(); i++)
	//{
	//	wildfire[i]->Propagate(dt);
	//}

}

void Environment::advance_withoutHeap()
{
	double dt = 1;
	time += dt;

	for (int i = 0; i != wildfire.size(); i++)
	{
		wildfire[i]->Propagate_withoutHeap(dt);
	}

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

Cell * Environment::getCell(Vertex & v)
{
	return getCell(findCell(v));
}

int Environment::findCell(double& x, double& y)
{
	// Returning the fuel of type 0 if the vertex cross the forest
	if (x == GRID_SIDE || y == GRID_SIDE || x == 0 || y == 0)
	{
		return -1;
	}

	int step = GRID_SIDE / CELL_SIDE;

	int i = static_cast<int>(x / CELL_SIDE);
	int j = static_cast<int>(y / CELL_SIDE);

	int cellIndex = step * i + j;
	return cellIndex;
}

int Environment::findCell(Vertex& v)
{
	v.cellIndex = findCell(v.x, v.y);
	return v.cellIndex;
}


void Environment::addFire(double Xi, double Yi)
{
	wildfire.push_back(
		new Fire(Xi, Yi)
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
			grid[i][j]->setR(U, theta);
		}
	}

	// Recalculate all timesteps
	calcAll();
}

void Environment::setTheta(double _theta){
	theta = _theta;

	int step = GRID_SIDE / CELL_SIDE;
	for (int i = 0; i != step; i++)
	{
		for (int j = 0; j != step; j++)
		{
			grid[i][j]->setR(U, theta);
		}
	}

	// Recalculate all timesteps
	calcAll();
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


void Environment::calcAll()
{
	// First cancel all the old entries
	timeHeap = PriorityQueue();
	
	// Recalculate all propagation for all vertices
	for(int i = 0; i != wildfire.size(); i++)
	wildfire[i]->calcVelocities();

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

void Environment::addMountain(double h, double pos[2], double lar)
{
	int step = GRID_SIDE/CELL_SIDE;
	double x0, y0, x1, y1;
	double h0, h1, h2, h3;
	double sigma = 2*lar;

	for(int i = 0; i != step; i++)
	for(int j = 0; j != step; j++)
	{
		// Compute the vertex coordinate of the cell 
		// rescalated for using in the heigth function
		x0 = CELL_SIDE*i - pos[0];
		y0 = CELL_SIDE*j - pos[1];
		x1 = CELL_SIDE*(i+1) - pos[0];
		y1 = CELL_SIDE*(j+1) - pos[1];

		// Compute of the heigth at cell borders
		h0 = h*std::exp( -(x0*x0 + y0*y0)/sigma);
		h1 = h*std::exp( -(x0*x0 + y1*y1)/sigma);
		h2 = h*std::exp( -(x1*x1 + y0*y0)/sigma);
		h3 = h*std::exp( -(x1*x1 + y1*y1)/sigma);

		// Adding the heigth mean and the derivative value in every cell
		grid[i][j]->height += (h0 + h1 + h2 + h3)/4;
		grid[i][j]->slope[0] += (h0 + h1 - h2 - h3)/(2*CELL_SIDE);
		grid[i][j]->slope[1] += (h0 + h2 - h1 - h3)/(2*CELL_SIDE);

		grid[i][j]->setR(U, theta);
	}

	calcAll();
}

void Environment::setCellType(double& x, double& y, int fNumber)
{
	Cell* cella = getCell(x, y);

	cella->fuelNumber = fNumber;
	cella->fuelIndex = cella->numberToIndex(fNumber);
	cella->setR(U, theta);
}