#include "Fuel.hxx"
#include "Rothermel.hxx"

#include <iostream>

void Fuel::setR0(double M_f)
{
	if (w_0 == 0 && SAV == 0 && delta == 0 && M_x == 0)
	{
		R0 = 0;
		return;
	}

	R0 = Rothermel_R0(this, M_f);
}

double Fuel::getWindFactor(double U)
{
	return Rothermel_WindFactor(this, U);
}

double Fuel::getSlopeFactor(double tan_phi)
{
	return Rothermel_SlopeFactor(this, tan_phi);
}
