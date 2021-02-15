#include "Fuel.hxx"
#include "Rothermel.hxx"
#include "Rothermel2.hxx"

#include <iostream>

void Fuel::setR0(double M_f)
{
	if (HETEROGENEOUS_FUEL)
	{
		R0 = Rothermel2_R0(this, M_f);
	}
	else
	{
		R0 = Rothermel_R0(this, M_f);
	}
}

double Fuel::getWindFactor(double U)
{
	if (HETEROGENEOUS_FUEL)
	{
		return Rothermel2_WindFactor(this, U);
	}
	else
	{
		return Rothermel_WindFactor(this, U);
	}
}

double Fuel::getSlopeFactor(double tan_phi)
{
	if (HETEROGENEOUS_FUEL)
	{
		return Rothermel2_SlopeFactor(this, tan_phi);
	}
	else
	{
		return Rothermel_SlopeFactor(this, tan_phi);
	}
}
