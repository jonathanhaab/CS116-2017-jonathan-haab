#include <iostream>
#include <fstream>

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
	vector<Neuron> neurons;
	
	Neuron neuron1;
	Neuron neuron2;
	
	neurons.push_back(neuron1);
	neurons.push_back(neuron2);


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
		

		for(size_t i(0); i < neurons.size(); ++i) {
			neurons_potential << "Neuron " << i+1 << "\t "<< neurons[i].getV() << "\t" << " mV at t = " << simStep*h << " ms " << "\t";
		}

			
			neurons_potential << "\t ";
			
		
		
		neurons_potential << "\n";
		
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
