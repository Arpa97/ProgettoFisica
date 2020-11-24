/*****************************************************************************************************
 *
 * Function that compute the rate of speed (RoS or R) of a 
 * surface fire for a specific type of fuel, based on the
 * Rothermel spread model.
 * 


*************************************** INPUT PARAMETERS ***************************************

-------------------------------------- Fuel particle --------------------------------------
Parameters intrinsic to the fuel particle, held constant for all types of fuel.
* h: Low heat content (Btu/lb). Heat released during combustion. 8 Btu/lb
* S_T: Total mineral (ash) content (fraction). 0.0555 lb minerals/lb wood
* S_e: Effective mineral content (fraction). 0.010 (lb minerals � lb silica)/lb wood
* rho_p: Oven-dry particle density (lb/ft3). 32 lb/ft3

-------------------------------------- Fuel array --------------------------------------
* w_0: Oven-dry fuel load (lb/ft2).
* SAV (or sigma): Surface-area-to-volume ratio (ft2/ft3).
* delta: Fuel bed depth (ft).
* M_x: Dead fuel moisture of extintion (fraction), at which spread rate will fall to zero.

-------------------------------------- Environmental --------------------------------------
* M_f: Moisture content (fraction). Dry weight basis, lb moisture/lb wood.
* U: Wind velocity at midflame height (ft/min).
* tan_phi: Maximum slope stepness (fraction). To be implemented.


*************************************** MODEL PARAMETERS ***************************************

-------------------------------------- Final components --------------------------------------
 * R: Rate of spread (ft/min)
 * I_R: Reaction intensity (Btu/ft2/min)
 * csi: Propagating flux ratio (fraction)
 * rho_b: Bulk density (lb/ft3)
 * epsilon: Effective heating number (fraction)
 * Q_ig: Heat of preignition (Btu/lb)
 * phi_w: Wind factor (dimensionless)
 * phi_s: Slope factor (dimensionless). 

 ----------------------------------- Intermediate components -----------------------------------
 * lambda: Optimum reaction velocity (min-1)
 * lambda_max: Maximum reaction velocity (min-1)
 * beta_op: Optimum packing ratio (fraction)
 * beta: Packing ratio (fraction)
 * rho_b: Oven-dry bulk density (lb/ft3)
 * w_n: Net fuel load (lb/ft2)
 * eta_M: Moisture damping coefficient (dimensionless)
 * eta_s: Mineral damping coefficient (dimensionless)


*************************************** CONVERSIONS ***************************************
* 1 ft/min = 0.00508 m/s
* 1 Btu = 1055.06 J
* 1 lb = 0.453592 kg
* 1 ft = 0.3048 m
* 1 ft2 = 0.092903 m2
* 1 ft3 = 0.0283168 m3
* 1 ton = 2000 lb
* 1 acre = 43560 ft2
 
*****************************************************************************************************/


#pragma once

struct Fuel;

double Rothermel_R0(Fuel* fuel, double _M_f);

double Rothermel_WindFactor(Fuel* fuel, double U);

double Rothermel_SlopeFactor(Fuel* fuel, double tan_phi);

double Rothermel_R(double R0, double phi_w, double phi_s = 0);

//R0 in ft/min, R in m/s