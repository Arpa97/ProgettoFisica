/*********************************************************************
 *
 * Constant definitions. Some of this values will be inserted
 * or selected by the user in the final program.
 *
 *********************************************************************/

#pragma once 

#define MOISTURE_CONTENT 0.1					// fraction. Not changing run-time
#define WIND_SPEED 2.2							// m/s. Can change run-time

#define CELL_SIZE 1e2							// m2.
#define GRID_SIZE 1e4							// m2.
#define MAX_DISTANCE 0.5						// m. Maximum distance between two vertices of the fire polygon.

#define N_FUEL_TYPES 53							// Number of different fuel types.
#define FUEL_PATH "FuelTypes.txt"			