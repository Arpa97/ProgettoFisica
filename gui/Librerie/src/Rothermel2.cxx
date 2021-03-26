#include "Rothermel2.hxx"
#include "Fuel.hxx"
#include <cmath>
#include <iostream>

using std::exp;
using std::pow;
using std::vector;

double Rothermel2_R0(Fuel* fuel, double _M_f)	//in ft/min
{
	double h = fuel->h;
	double S_T = fuel->S_T;
	double S_e = fuel->S_e;
	double rho_p = fuel->rho_p;
	vector<vector<double>> w_0 = fuel->w_0;
	const vector<vector<double>> SAV = fuel->SAV;
	double delta = fuel->delta;
	
	double M_x[2];
	M_x[0] = fuel->M_x;
	vector<double> M_f[2];

	double R0 = 0, I_R, csi, rho_b;
	double lambda, lambda_max, beta_op, beta, sigma;
	double A;

	vector<double> A2[2], f2[2], g[2], w_n2[2], Q_ig2[2];
	double A1[2], f1[2], w_n1[2], h1[2], S_e1[2], eta_s[2], M_f1[2], eta_M[2], r_M[2], sigma1[2];
	double A_T;
	double W, M_f_dead;

	size_t sizes[2]{ w_0[0].size(), w_0[1].size() };	//live and dead fuels have a different number of size classes

	//Filling M_f. In this version all fuels have the same moisture content
	for (int i = 0; i < 2; i++)
	{
		M_f[i] = vector<double>(sizes[i]);
		for (int j = 0; j < sizes[i]; j++)
		{
			M_f[i][j] = _M_f;					
		}
	}

	//Conversion due to curing for dynamical models
	if (fuel->type == 'D')
	{
		double T;
		if (M_f[1][0] < 0.3)
		{
			T = 1;
		}
		else if (M_f[1][0] > 1.2)
		{
			T = 0;
		}
		else
		{
			double T = -1.11 * M_f[1][0] + 1.33;
		}
		w_0[0][3] = T * w_0[1][0];
		w_0[1][0] = w_0[1][0] - T * w_0[1][0];
	}


	A_T = 0;
	for (int i = 0; i < 2; i++)
	{
		A1[i] = 0;
		A2[i] = vector<double>(sizes[i]);
		for (int j = 0; j < sizes[i]; j++)
		{
			A2[i][j] = SAV[i][j] * w_0[i][j] / rho_p;
			A1[i] += A2[i][j];
		}
		A_T += A1[i];
	}

	for (int i = 0; i < 2; i++)
	{
		f1[i] = A1[i]/A_T;
		f2[i] = vector<double>(sizes[i]);
		for (int j = 0; j < sizes[i]; j++)
		{
			if (A1[i] != 0)
			{
				f2[i][j] = A2[i][j] / A1[i];
			}
			else
			{
				f2[i][j] = 0;
			}
		}
	}

	double g_subclass[2][6] = { {0,0,0,0,0}, {0,0,0,0,0} };
	for (int i = 0; i < 2; i++)
	{
		g[i] = vector<double>(sizes[i]);
		for (int j = 0; j < sizes[i]; j++)
		{
			if (SAV[i][j] >= 1200)
			{
				g[i][j] = 0;
				g_subclass[i][0] += f2[i][j];
			}
			else if (SAV[i][j] >= 192)
			{
				g[i][j] = 1;
				g_subclass[i][1] += f2[i][j];
			}
			else if (SAV[i][j] >= 96)
			{
				g[i][j] = 2;
				g_subclass[i][2] += f2[i][j];
			}
			else if (SAV[i][j] >= 48)
			{
				g[i][j] = 3;
				g_subclass[i][3] += f2[i][j];
			}
			else if (SAV[i][j] >= 16)
			{
				g[i][j] = 4;
				g_subclass[i][4] += f2[i][j];
			}
			else
			{
				g[i][j] = 5;
			}
		}
		g_subclass[i][5] = 0;

		for (int j = 0; j < sizes[i]; j++)
		{
			g[i][j] = g_subclass[i][(size_t)g[i][j]];
		}
	}

	double Wnum = 0, Wden = 0;
	for (int j = 0; j < sizes[0]; j++)
	{
		Wnum += w_0[0][j] * exp(-138 / SAV[0][j]);
	}
	for (int j = 0; j < sizes[1]; j++)
	{
		Wden += w_0[1][j] * exp(-500 / SAV[1][j]);
	}
	W = Wnum / Wden;

	double M_f_deadNum = 0, M_f_deadDen = 0;
	for (int j = 0; j < sizes[0]; j++)
	{
		M_f_deadNum += M_f[0][j] * w_0[0][j] * exp(-138 / SAV[0][j]);
		M_f_deadDen += w_0[0][j] * exp(-138 / SAV[0][j]);
	}
	M_f_dead = M_f_deadNum / M_f_deadDen;

	M_x[1] = 2.9 * W * (1 - M_f_dead / M_x[0]) - 0.226;

	for (int i = 0; i < 2; i++)
	{
		w_n1[i] = 0;
		w_n2[i] = vector<double>(sizes[i]);
		for (int j = 0; j < sizes[i]; j++)
		{
			w_n2[i][j] = w_0[i][j] * (1 - S_T);
			w_n1[i] += g[i][j] * w_n2[i][j]; 
		}
	}

	for (int i = 0; i < 2; i++)
	{
		h1[i] = 0;
		S_e1[i] = 0;
		M_f1[i] = 0;
		sigma1[i] = 0;
		for (int j = 0; j < sizes[i]; j++)
		{
			h1[i] += f2[i][j] * h;
			S_e1[i] += f2[i][j] * S_e;
			M_f1[i] += f2[i][j] * M_f[i][j];
			sigma1[i] += f2[i][j] * SAV[i][j];
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (S_e1[i] != 0)
		{
			eta_s[i] = 0.174 * pow(S_e1[i], -0.19);
		}
		else
		{
			eta_s[i] = 0;
		}

		r_M[i] = M_f1[i] / M_x[i];
		eta_M[i] = 1 - 2.59 * r_M[i] + 5.11 * pow(r_M[i], 2) - 3.52 * pow(r_M[i], 3);
	}

	sigma = rho_b = beta = 0;
	for (int i = 0; i < 2; i++)
	{
		sigma += f1[i] * sigma1[i];
		for (int j = 0; j < sizes[i]; j++)
		{
			rho_b += w_0[i][j] / delta;
			beta += w_0[i][j] / (delta * rho_p);
		}
	}

	beta_op = 3.348 * pow(sigma, -0.8189);

	lambda_max = pow(sigma, 1.5) / (495 + 0.0594 * pow(sigma, 1.5));
	A = 133 * pow(sigma, -0.7913);
	lambda = lambda_max * pow(beta / beta_op, A) * exp(A * (1 - beta / beta_op));

	I_R = 0;
	for (int i = 0; i < 2; i++)
	{
		I_R += lambda * w_n1[i] * h1[i] * eta_M[i] * eta_s[i];
	}

	csi = pow(192 + 0.2595 * sigma, -1) * exp((0.792 + 0.681 * pow(sigma, 0.5)) * (beta + 0.1));

	for (int i = 0; i < 2; i++)
	{
		Q_ig2[i] = vector<double>(sizes[i]);
		for (int j = 0; j < sizes[i]; j++)
		{
			Q_ig2[i][j] = 250 + 1116 * M_f[i][j];
		}
	}

	double sink = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < sizes[i]; j++)
		{
			sink += rho_b * f1[i] * f2[i][j] * exp(-138 / SAV[i][j]) * Q_ig2[i][j];
		}
	}

	fuel->params[0] = beta;
	fuel->params[1] = beta_op;
	fuel->params[2] = sigma;
	fuel->params[3] = I_R;

	fuel->Umax = 0.9 * I_R * 0.00508;

	R0 = I_R * csi / sink;
	return R0;
}


double Rothermel2_WindFactor(Fuel* fuel, double U)
{
	double beta = fuel->params[0];
	double beta_op = fuel->params[1];
	double sigma = fuel->params[2];
	double I_R = fuel->params[3];
	double B, C, E;
	U /= 0.00508;

	B = 0.02526 * pow(sigma, 0.54);
	C = 7.47 * exp(-0.133 * pow(sigma, 0.55));
	E = 0.715 * exp(-3.59e-4 * sigma);

	if (WIND_LIMIT)
	{
		if (U > 0.9 * I_R)
		{
			U = 0.9 * I_R;
		}
	}

	double phi_w = C * pow(U, B) * pow(beta / beta_op, -E);
	return phi_w;
}


double Rothermel2_SlopeFactor(Fuel* fuel, double tan_phi)
{
	double beta = fuel->params[0];

	double phi_s = 5.275 * pow(beta, -0.3) * pow(tan_phi, 2);
	return phi_s;
}

//in ft/min
double Rothermel2_R(double R0, double phi_w, double phi_s)
{
	double R = R0 * (1 + phi_w + phi_s);
	return R;
}