/**
 * @file   neuronMain.cpp
 * @Author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  Main programm to simulate a network of neurons
 */


#include <iostream>
#include <fstream>
#include <array>
#include <random>
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
	for(size_t i(0); i < N_e; ++i){
		neurons[i] = (new Neuron(EXCITATORY));
	}
	// Initialisation des inhibitory
	for(size_t i(N_e); i < neurons.size(); ++i){
		neurons[i] = (new Neuron(INHIBITORY));
	}
	
	// Initialisation du network à 0
	for(size_t i(0); i < network.size(); ++i){
		for(size_t j(0); j < network[i].size(); ++j){
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
			
			network[dis(gen)][i] += 1;
		}
			// ... inhibitory
		for(int j(0); j < C_i; ++j){
			
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(N_e, N_i-1);
		
			network[dis(gen)][i] += 1;
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
	
	neurons_potential << "\t" << simStep*h;
	
	while(simStep <= total_steps) {
		
		if((simStep >= a/h) and (simStep <= b/h)) {
			
			current_i = iExt;
			
		} else {
			
			current_i = 0;
		}
		
		for(int i(0); i < N; ++i){
			
			if(neurons[i]->update(current_i, simStep)){ // Si update return true => neuron[i] spike
				
				for(int j(0); j < N; ++j){ // On va donner un potentiel additionnel aux neurones auxquels neuron[i] est connecté
					
					if(network[i][j] != 0){ // càd si i est connecté avec j
						
						neurons[j]->receive(simStep-1, network[i][j]*neurons[i]->getJ()); //On multiplie par network[i][j] parce que i peut être lié plusieurs fois à j
					}
				}
			}
			
			neurons_potential << "\t" << neurons[i]->getV();
		
		}
		
		neurons_potential << "\n";
		
		simStep += 1; 
	}
	
	// Désalocation des pointeurs
	for(size_t i(0); i < N; ++i){
		delete neurons[i];
	}
	
	// Fermeture des stream
	neurons_potential.close();
	
	return 0;
}
