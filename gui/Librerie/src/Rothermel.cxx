#include "Rothermel.hxx"
#include "Fuel.hxx"
#include <cmath>
#include <iostream>

using std::exp;
using std::pow;

double Rothermel_R0(Fuel* fuel, double _M_f)
{
	double h = fuel->h;
	double S_T = fuel->S_T;
	double S_e = fuel->S_e;
	double rho_p = fuel->rho_p;
	double w_0 = fuel->w_0;
	double SAV = fuel->SAV;
	double delta = fuel->delta;
	double M_x = fuel->M_x;
	double M_f = _M_f;

	double R0, I_R, csi, rho_b, epsilon, Q_ig;
	double lambda, lambda_max, beta_op, beta, w_n, eta_M, eta_s;
	double A, r_M;

	A = 133 * pow(SAV, -0.7913);
	lambda_max = pow(SAV, 1.5) / (495 + 0.0594 * pow(SAV, 1.5));
	beta_op = 3.348 * pow(SAV, -0.8189);
	rho_b = w_0 / delta;
	beta = rho_b / rho_p;
	lambda = lambda_max * pow(beta / beta_op, A) * exp(A * (1 - beta / beta_op));
	w_n = w_0 * (1 - S_T);
	r_M = M_f / M_x;
	eta_M = 1 - 2.59 * r_M + 5.11 * pow(r_M, 2) - 3.52 * pow(r_M, 3);
	eta_s = 0.174 * pow(S_e, -0.19);

	I_R = lambda * w_n * h * eta_M * eta_s;
	csi = exp((0.792 + 0.681 * pow(SAV, 0.5)) * (beta + 0.1)) / (192 + 0.2595 * SAV);
	epsilon = exp(-138 / SAV);
	Q_ig = 250 + 1116 * M_f;

	R0 = (I_R * csi) / (rho_b * epsilon * Q_ig);
	return R0;
}


double Rothermel_WindFactor(Fuel* fuel, double U)
{
	double rho_p = fuel->rho_p;
	double w_0 = fuel->w_0; 
	double SAV = fuel->SAV;
	double delta = fuel->delta;
	double beta, beta_op, rho_b, B, C, E;
	U /= 0.00508;

	beta_op = 3.348 * pow(SAV, -0.8189);
	rho_b = w_0 / delta;
	beta = rho_b / rho_p;
	B = 0.02526 * pow(SAV, 0.54);
	C = 7.47 * exp(-0.133 * pow(SAV, 0.55));
	E = 0.715 * exp(-3.59e-4 * SAV);

	double phi_w = C * pow(U, B) * pow(beta / beta_op, -E);
	return phi_w;
}


double Rothermel_SlopeFactor(Fuel* fuel, double tan_phi)
{
	double rho_p = fuel->rho_p;
	double w_0 = fuel->w_0;
	double delta = fuel->delta;
	double rho_b, beta;

	rho_b = w_0 / delta;
	beta = rho_b / rho_p;

	double phi_s = 5.275 * pow(beta, -0.3) * pow(tan_phi, 2);
	return phi_s;
}


double Rothermel_R(double R0, double phi_w, double phi_s)
{
	double R = R0 * (1 + phi_w + phi_s);
	return R;
}