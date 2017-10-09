#include <iostream>
#include <vector>
#include <Time.hpp>
 
#ifndef NEURON_H
#define NEURON_H

class Neuron
{
	public :
		//Constructeur
		Neuron(double c);
		
		void update(sf::Time h, double iExt, sf::Time simTime);
		
		ostream& showSpikes();
		
	private :
		double V; // Potentiel de dépolarisation
		vector<sf::Time> spikes; // pour mémoriser le temps de chaque spike , ON RECUPERE LE NB DE SPIKES GRACE A LA TAILLE DU VECTOR
		
		double c; // Connections reçues par le neurone
		
};

	const double Neuron::neuron_number(0); /// à changer
	const double Neuron::excitatory_number(0.8*neuron_number);
	const double Neuron::inhibitory_number(0.2*neuron_number;
	
	const double Neuron::gamma(0.25); /// à changer
	const double Neuron::excitatory_c(1); /// à changer
	const double Neuron::inhibitory_c(gamma*excitatory_c);
	const double Neuron::exterior_c(excitatory_c);
	
	const sf::Time Neuron::tau_exterior(milliseconds(20)); //ms
	const sf::Time Neuron::tau(milliseconds(2)); //ms
	const double Neuron::teta(20); mV
	const double Neuron::reset_potential(10);

/*
 * PARAMETRES
 * 
 * g : force relative des synapses inhibiteurs
 * 
 * vext : fréquence external imput
 * 
 * J : amplitude du EPSP (excitatory post synaptic potential
 * 
 * Ce : nb de connections excitatory
 * 
 * D : délai de transmission
 * 
 * 
*/




#endif
