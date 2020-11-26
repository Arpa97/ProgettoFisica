/*********************************************************************
 *
 * Constant definitions. Some of this values will be inserted
 * or selected by the user in the final program.
 *
 *********************************************************************/

#pragma once 

#define MOISTURE_CONTENT 0.1					// fraction. Not changing run-time
#define WIND_SPEED 2.2							// m/s. Can change run-time
#define WIND_DIRECTION 0	                // Clock-wise from y axis, in �

#define CELL_SIDE 10							// m. Length of the cell (square) side. Cannot be chosen by user.
#define GRID_SIDE 400							// m. Length of the grid size. Must be a multiple of CELL_SIDE. Can be chosen by user.
#define MAX_DISTANCE 0.5						// m. Maximum distance between two vertices of the fire polygon.

#define N_FUEL_TYPES 53							// Number of different fuel types.
#define FUEL_PATH "FuelTypes.txt"

#define TIMESTEP 10								// s.
