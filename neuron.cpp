#include <iostream>
#include "neuron.hpp"

#include <cmath>

using namespace std;


Neuron::Neuron()
	: localStep(0), J(0)
{
	state = INHIBITORY;
	v = v_res; //mV
	spikes.clear();
	ringBuffer.clear();
}


void Neuron::update(double h, double iExt, double simStep)
{
	updateState(h, simStep);
	
	if(state == EXCITATORY) {

		/// Potentiel de la membrane
		double r(tau/c);
		
		
		if(ringBuffer.find(simStep) == ringBuffer.end()) {
			
			v = exp(-h/tau)*v + iExt*r*(1-exp(-h/tau)); // Pas de J à cette step
	
		} else {
			v = exp(-h/tau)*v + iExt*r*(1-exp(-h/tau)) + ringBuffer[simStep]; // Ajout du J à cette step
		}
		
		
		
		/// Spike (20mV)
		if(v > v_th) {
			J = v; // On donne à J toute la décharge
			v = v_res;
			spikes.push_back(simStep);
		}
		
	} else {
		
		v = v_res; // refractory
		
	}
	
	localStep += 1;
}

void Neuron::updateState(double h, double simStep)
{
	if(spikes.empty() or abs(spikes.back() - (localStep*h)) > refractoryTime) {
		state = EXCITATORY;
	} else {
		state = INHIBITORY;
	}
}

vector<long> Neuron::getSpikesTime()
{
	return spikes;
}

double Neuron::getV()
{
	return v;
}

double Neuron::getJ()
{
	return J;
}

bool Neuron::isSpiking()
{
	
	if(!(spikes.empty()) and (abs(localStep - spikes.back()) < 1e-1)){
		return true;
	}
	
	return false;
}


void Neuron::receive(long step, double J) 
{
	if(ringBuffer.find(step) == ringBuffer.end()) {
		
		ringBuffer.insert(std::make_pair(step, J));
		
	} else {
		
		ringBuffer[step] += J;// On cumule les différents J
		
	}
}
