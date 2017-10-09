#include <iostream>

#include "neuron.hpp"
#include "neuron.cpp"
#include <Time.hpp>

using namespace std;

CONST VRESET(-70);

int main()
{
	// Time
	sf::Time startTime(Zero);
	sf::Time stopTime(milliseconds(1000));
	sf::Time h(milliseconds(0.1));
	//sf::Time tauRef(milliseconds(2)); // ??
	
	sf::Time simTime(startTime);
	
	// Variable
	double iExt(400);

	int nbSpikes(100);
	
	Neuron neuron(250); /// on doit lui donné un nombre de connections
	
	while(simTime < stopTime) {
		
		neuron.update(h, iExt, simTime);
		
		simTime += h;
	}
	
	neuron.showSpikes();
		
	
	
	return 0;
}


/*
 * 
 * 
 * 
 * ------------
 *  C = 250 pF
 * 	Tau = 10 ms
 *  Tau ref = 2ms
 *  Vreset = -70 mV => après un  spike
 *  h = 0.1 ms
 *  -----------
 * 
 * D'après le texte 
 * tauE = 20 ms
 * Vmax ou teta = 20 mV
 * Vr = 10 mV
 * tau = 2 ms
 * 
 */
