/*********************************************************************
 *
 * Constant definitions. Some of this values will be inserted
 * or selected by the user in the final program.
 *
 *********************************************************************/

#pragma once 

#define MOISTURE_CONTENT 0.1					// fraction. Not changing run-time

#define CELL_SIDE 10							// m. Length of the cell (square) side. Cannot be chosen by user.
#define GRID_SIDE 400							// m. Length of the grid size. Must be a multiple of CELL_SIDE. Can be chosen by user.
#define MAX_DISTANCE 7							// m. Maximum distance between two vertices of the fire polygon.

#define N_FUEL_TYPES 53							// Number of different fuel types.
#define FUEL_PATH "FuelTypes.txt"

#define MAXWINDSPEED 10                         // m/s. Max wind speed
#define RANDOM true								// If true, srand is called
#define FIXED_FIRE false						// If true, fire is created always at the center of the grid
#define HETEROGENEOUS_FUEL true					// If true, Rothermel2 is used
#define WIND_LIMIT true							// If true, wind limit is applied

#define TOPOGRAPHIC_SLOPE 0.349		//20 deg		
#define TOPOGRAPHIC_ASPECT 1.5707	//90 deg
