#ifndef CONSTANTES_H
#define CONSTANTES_H



constexpr double h = 0.1;
constexpr long tau = 20; //ms
constexpr double tau_ref = 2; //ms
constexpr double refractoryTime = 2.0;
constexpr double v_th = 20; //mV
constexpr double v_res = 0;
		
constexpr double c = 1;
constexpr double R = 20e6; // 20.0 G ohm résistance de la membrane
constexpr int D_step = 15;
const double c1 = exp(-h/tau);
const double c2 = 1-exp(-h/tau);

constexpr double J_e = 0.1;
constexpr double J_i = -0.5;

constexpr int N(12500); // Total number of neurons
constexpr int N_e(0.8*N); // Number of excitatory neurons
constexpr int N_i(0.2*N); // Number of inhibitory neurons
constexpr int C_e(N_e*0.1); // Number of connections with excitatory neurons
constexpr int C_i(N_i*0.1); // Number of conncections with inhibitory neurons











#endif
