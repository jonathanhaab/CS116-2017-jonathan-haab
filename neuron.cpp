#include <iostream>
#include "neuron.hpp"

#include <random>

using namespace std;


Neuron::Neuron(Type type)
	: localStep(0), type(type)
{

	state = INHIBITORY;
	v = v_res; //mV
	spikes.clear();
	ringBuffer.resize(D_step + 1);
	
	if(type = INHIBITORY){
		J = J_i;
	}
	
	if(type = EXCITATORY){
		J = J_e;
	}
}

bool Neuron::update(double iExt, double simStep)
{
	bool isSpiking(false);
	
	updateState(localStep);
	
	if(state == ACTIVE) {


		// Distribution de poisson
		poisson_distribution<> poisson(Vext*C_e*h*J);
		random_device rd;
		mt19937 gen(rd());
		
		/// Potentiel de la membrane
		double r(tau/c);
		int x(simStep);
		
		v = c1*v + c2*iExt*r + ringBuffer[x%(D_step+1)] + poisson(gen);
		
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
	if(spikes.empty() or abs(spikes.back() - (simStep))*h > refractoryTime) {
		state = ACTIVE;
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

Type getType()
{
	return type;
}



void Neuron::setType(Type newType)
{
	type = newType;
}


void Neuron::receive(long step, double J) 
{
	int x(step);
	ringBuffer[x%(D_step+1)] += J;
}
