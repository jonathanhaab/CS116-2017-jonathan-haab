#include <iostream>
#include "neuron.hpp"

#include <cmath>

using namespace std;

//--------


Neuron::Neuron(double c)
	: c(c)
{
	V = reset_potential; //mV
	spikesTime.clear();
}


void Neuron::update(sf::Time h, double iExt, sf::Time simTime)
{
	/// Spike (-55mV)
	if(V > teta) {
		V = reset_potential;
		spikesTime.pushback(simTime);
	}
	
	/// Potentiel de la membrane
	double r(tau/c);
	
	V = exp(-h/tau)*V + iExt*r/tau*(1-exp(-h/tau));
	
}

ostream& Neuron::showSpikes()
{
	ostream out;
	
	out << "le nombre de spike effectués est : " << spikes.size() << endl;
	
	out << "n°			temps" << endl;
	for(size_t i(0); i < spikes.size(); ++i) {
		
		out << i << "			" << spikes[i] << endl; 
		
	}
	
	return out;
}
