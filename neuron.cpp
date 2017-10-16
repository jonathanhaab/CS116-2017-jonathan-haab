#include <iostream>
#include "neuron.hpp"

using namespace std;


Neuron::Neuron()
	: localStep(0), J(0.1)
{
	state = INHIBITORY;
	v = v_res; //mV
	spikes.clear();
	ringBuffer.resize(D_step + 1);
}

bool Neuron::update(double iExt, double simStep)
{
	bool isSpiking(false);
	
	updateState(localStep);
	
	if(state == EXCITATORY) {

		/// Potentiel de la membrane
		double r(tau/c);
		int x(simStep);
		v = c1*v + iExt*r*c2 + ringBuffer[x%(D_step+1)]; // Ajout du J à cette step
		
		/// Réinitialisation de la cellule du ringBuffer qui vient d'être utilisée
		ringBuffer[x%(D_step+1)] = 0;
		
		/// Spike (20mV)
		if(v > v_th) {
			v = v_res;
			spikes.push_back(simStep);
			isSpiking = true;
		}
		
	} else {
		
		v = v_res; // refractory
		
	}
	
	localStep += 1;
	
	return isSpiking;
}

void Neuron::updateState(double simStep)
{
	if(spikes.empty() or abs(spikes.back() - (localStep))*h > refractoryTime) {
		state = EXCITATORY;
	} else {
		state = REFRACTORY;
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


void Neuron::receive(long step, double J) 
{
	int x(step);
	ringBuffer[x%(D_step+1)] += J;
}
