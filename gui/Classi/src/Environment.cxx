#include "Environment.hxx"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip> 
#include <fstream>
#include <filesystem>

using std::cout;
using std::endl;

Cell* Environment::nullFuel = new Cell(0, 0);

Environment::Environment(const std::vector<std::vector<double>> &fuelPercentages, double moistureContent)
{
	U = 0;
    theta = 0;
    M_f = moistureContent;
	Cell::FillFuelType(M_f);
	nullFuel->setR(0);
	Fire::setEnvironment(this);

	int step = GRID_SIDE / CELL_SIDE;	
	int fuelNumber, number;
	double validator;

    int nDifferentFuels = (int)fuelPercentages.size();

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
            if (nDifferentFuels == 0) fuelNumber = 1;
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

    // Check to limit the maximum moisture of the forest
	double M_fmax = getMaximumMoisture();
    M_f = M_f < M_fmax ? M_f : M_fmax;

	// Path of the Models folder
	outputFile = std::filesystem::current_path();
	outputFile.replace_filename("File/output.dat");

	// Path to the file
	std::string Path = outputFile.string();

	std::ofstream file = std::ofstream(Path.data(), std::ofstream::out);

	file << "File con i dati interessanti della simulazione:\n"; 
	file.close();
}

Environment::Environment(std::string Modello, double moistureContent)
{
	//-----Inizializing the principal variables-----
	U = 0;
    theta = 0;
    M_f = moistureContent;
	Cell::FillFuelType(M_f);
	nullFuel->setR(0);
	Fire::setEnvironment(this);

	// Variables for the calculation on the grid
	int step = GRID_SIDE / CELL_SIDE;

	// Inizializing the grid
	grid = new Cell * *[step];
	for (int i = 0; i != step; i++)
		grid[i] = new Cell * [step];

	//-----Inizializing the model-----

	// Path of the Models folder
	std::filesystem::path p = std::filesystem::current_path();
	p.replace_filename("File/Models/");

	if (!std::filesystem::exists(p))
	{
		for (int i = 0; i < 4; i++)
		{
			p = p.parent_path();
		}

		p.replace_filename("File/Models/");
	}

	// Path to the file
	std::string Path = p.string() + Modello;

	// Open the file
	std::ifstream file (Path.data(), std::ifstream::in);

	// Control if the file is fine
	if(!file.good())
	{
		cout << "Model not found, program aborting..." << endl;
		abort();
	}

	//-----Reading the file-----
	
	// Skip the first line for the comment
	getline(file, Modello, '\n');

	// Control that the number on the second line correspond to STEP
	getline(file, Modello, '\n');

	if(step != stoi(Modello))
	{
		cout << "Model loaded not compatible with current forest, program aborting..."<< endl;
		abort();
	}

	// Skipping another line
	getline(file, Modello, '\n');

	// Inizialize the forest
	for(int cInd = 0; cInd != step*step; cInd++)
	{
		int j = cInd % step;
		int i = (cInd - j) / step;

		getline(file, Modello, '\n');

		grid[i][j] = new Cell(stoi(Modello), 0);
	}

	// Skipping another line
	getline(file, Modello, '\n');
	double Height;

	// Inizialize the Height
	for(int cInd = 0; cInd != step*step; cInd++)
	{
		int j = cInd % step;
		int i = (cInd - j) / step;

		file >> Height;

		grid[i][j]->height = Height;
		grid[i][j]->setR(U, theta);
	}

	// Closing the file
	file.close();

	//-----General settings-----

	// Check to limit the maximum moisture of the forest
	double M_fmax = getMaximumMoisture();
    M_f = M_f < M_fmax ? M_f : M_fmax;

	// Path of the Models folder
	outputFile = std::filesystem::current_path();
	outputFile.replace_filename("File/output.dat");

	// Inizializing the outputFile
	Path = outputFile.string();

	std::ofstream File = std::ofstream(Path.data(), std::ofstream::out);

	File << "File con i dati interessanti della simulazione:\n"; 
	File.close();
}

Environment::~Environment()
{

}

double Environment::getMaximumMoisture(){
    int step = GRID_SIDE / CELL_SIDE;
    double maxMoisture = 1;
    double M_x;
    std::vector<Fuel*> fuelsInForest = getFuelInfo();

    for (int i = 0; i != step; i++)
    {
        for (int j = 0; j != step; j++)
        {
			if(grid[i][j]->fuelIndex == 0)
				continue;

            M_x = fuelsInForest[grid[i][j]->fuelIndex]->M_x;
            maxMoisture = maxMoisture < M_x ? maxMoisture : M_x;
        }
    }
    // Remove 0.01 from the max moisture to avoid non-propagating fire
    maxMoisture = maxMoisture - 0.01;

    return maxMoisture;
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

	writeData();
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

	writeData();
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

void Environment::setMf(double _Mf){
	M_f = _Mf;

	Cell::FillFuelType(M_f);

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
        // rescalated for using in the height function
		x0 = CELL_SIDE*i - pos[0];
		y0 = CELL_SIDE*j - pos[1];
		x1 = CELL_SIDE*(i+1) - pos[0];
		y1 = CELL_SIDE*(j+1) - pos[1];

        // Compute of the height at cell borders
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

void Environment::setCellType(double x, double y, int fNumber)
{
	Cell* cella = getCell(x, y);

	cella->fuelNumber = fNumber;
	cella->fuelIndex = cella->numberToIndex(fNumber);
	cella->setR(U, theta);
}

double Environment::getBurnedArea()
{
	double totarea = 0;
	for (auto &fire : wildfire)
	{
		totarea += fire->area;
	}
	return totarea;
}

std::vector<Fuel*> Environment::getFuelInfo()
{
    std::vector<Fuel*> FuelVector;
    FuelVector.insert(FuelVector.end(), &Cell::FuelType[0], &Cell::FuelType[N_FUEL_TYPES + 1]);
    return FuelVector;
}

void Environment::saveModel(std::string name)
{
	int step = GRID_SIDE/CELL_SIDE;

	//-----Inizializing the model-----

	// Path of the Models folder
	std::filesystem::path p = std::filesystem::current_path();
	p.replace_filename("File/Models/");

	// Path to the file
	std::string Path = p.string() + name;

	// Open the file
	std::ofstream file (Path.data(), std::ofstream::out);

	// Writing the first things
	file << "Forest model: " << name << "\n";
	file << step << "\n";
	file << "Start:\n";

	//-----Writing the composition-----
	Cell * c;

	for(int i = 0; i != step*step; i++)
	{
		c = getCell(i);
		file << c->fuelIndex << "\n";
	}

	// Height
	file << "Heights:\n";

	for(int i = 0; i != step*step; i++)
	{
		c = getCell(i);
		file << c->height << "\n";
	}

	//-----Finishing-----
	file.close();
}

void Environment::writeData()
{
	// Inizializing the outputFile
	std::string Path = outputFile.string();

	std::ofstream file = std::ofstream(Path.data(), std::ofstream::out | std::ofstream::app);

	double xMax = 0;

	for(int i = 0; i != wildfire[0]->Polygon.size(); i++)
		xMax = xMax > wildfire[0]->Polygon[i].x ? xMax : wildfire[0]->Polygon[i].x;

	if(xMax <= X_BREAKPOINT)
	file << time << "\t" << xMax << "\n";

	file.close();
}

void Environment::createBarrier(double x, double y, int Alt, int Lar)
{
	// Iterate over the number of cell needed
	for(int i = 0; i != Alt; i++)
	{
		for(int j = 0; j != Lar; j++)
		{
			Cell* cella = getCell(x + i*CELL_SIDE, y + j*CELL_SIDE);

			// Setting the cell to fuel null
			cella->fuelNumber = 0;
			cella->fuelIndex = cella->numberToIndex(0);
			cella->setR(U, theta);
		}
	}
}