/*****************************************************************************************************
 *
 * Evolution of Rothermel surface fire model for heterogeneous fuels, 
 * with different classes of size and live and dead parts
 * 
 * 
 *****************************************************************************************************
 * Refer to Rothermel.hxx for parameter list and explanation.
 * Index i refers to live and dead category (i = 0 dead i = 1 live)
 * Index j refers to class size 
 * 
*****************************************************************************************************/


#pragma once

struct Fuel;

double Rothermel2_R0(Fuel* fuel, double _M_f);

double Rothermel2_WindFactor(Fuel* fuel, double U);

double Rothermel2_SlopeFactor(Fuel* fuel, double tan_phi);

double Rothermel2_R(double R0, double phi_w, double phi_s = 0);

//R0 in ft/min, R in m/s