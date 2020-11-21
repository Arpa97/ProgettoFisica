#include "Fuel.h"
#include "Rothermel.hxx"

#include <iostream>

void Fuel::setR0(double M_f)
{
	R0 = Rothermel_R0(this, M_f);
	//std::cerr << R0 << '\n';
}

double Fuel::getWindFactor(double U)
{
	return Rothermel_WindFactor(this, U);
}

double Fuel::getSlopeFactor(double tan_phi)
{
	return Rothermel_SlopeFactor(this, tan_phi);
}
