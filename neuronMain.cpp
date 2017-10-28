#include <iostream>
#include <fstream>
#include <array>
#include "neuron.hpp"


using namespace std;


int main()
{
/// Initialisation -----------------------------------------------------
	// Time
	const long startTime(0);
	const long stopTime(200);
	const double h(0.1);
	
	double total_steps(abs(stopTime-startTime)/h);
	
	// Interval de temps durant lequel on donne un courant au neurone
	long a;
	long b;
	
	long simStep(0);
	
	// Variable
	double iExt;
	
	// Neurones
	array<Neuron*, N> neurons;
	
	
	// Connections
	array<array<int, N>, N> network;
	
	
	// Initialisation des excitatory
	for(int i(0); i < N_e; ++i){
		neurons[i] = new Neuron(EXCITATORY);
	}
	// Initialisation des inhibitory
	for(int i(N_e); i < neurons.size(); ++i){
		neurons[i] = new Neuron(INHIBITORY);
	}
	
	// Initialisation du network à 0
	for(int i(0); i < network.size(); ++i){
		for(int j(0); j < network[i].size(); ++j){
			network[i][j] = 0;
		}
	}
	
	// Création de connections...
		
	for(int i(0); i < N; ++i){
			// ... excitatory
		for(int j(0); j < C_e; ++j){
			
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, N_e-1);
			
			network[dis][i] += 1;
		}
			// ... inhibitory
		for(int j(0); j < C_i; ++j){
			
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(N_e, N_i-1);
		
			network[dis][i] += 1;
		}
	}

/// Dialogue utilisateur -----------------------------------------------
	
	cout << "Enter the current's value : ";
	cin >> iExt;
	
	do{
		
		cout << "Enter the starting time of the current (between " << startTime << " and " << stopTime << " ms) : ";
		cin >> a;
	
	}while((a<startTime) or (a>stopTime));
	
	do{
	
		cout << "Enter the stoping time of the current (between " << a << " and " << stopTime << " ms) : ";
		cin >> b;
	
	}while((b<a) or (b>stopTime));
	
	
	
/// Lancement de la simulation -----------------------------------------
	
	std::ofstream neurons_potential;
	neurons_potential.open("Neurons_Potential.txt");
	
	double current_i;
	

	
	
	
	
	/*
	
	while(simStep <= total_steps) {
		
		if((simStep >= a/h) and (simStep <= b/h)) { 
			
			current_i = iExt;
			
		} else {
			
			current_i = 0;
		}
		
		if(neurons[0].update(current_i, simStep)){
			
			neurons[1].receive(simStep-1, neurons[0].getJ());
		}
		
		neurons[1].update(0, simStep);
		
		/*
		for(size_t i(0); i < neurons.size(); ++i) {
			neurons_potential << "Neuron " << i+1 << "\t "<< neurons[i].getV() << "\t" << " mV at t = " << simStep*h << " ms " << "\t";
		}
		
		
		neurons_potential << "\t "<< neurons[0].getV() << "\t" << simStep*h << "\t";

			
			
			//neurons_potential << "\t ";
			
		
		
		neurons_potential << "\n";
		*/
		
		simStep += 1; 
	}
		
	neurons_potential.close();
	
	return 0;
}


/*
 * 
 * 
 * 
 * 
 * D'après le texte 
 * tauE = 20 ms
 * Vmax ou teta = 20 mV
 * Vr = 10 mV
 * tau = 2 ms
 * 
 */
