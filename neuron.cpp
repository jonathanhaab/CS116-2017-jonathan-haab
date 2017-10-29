/**
 * @file   neuron.cpp
 * @Author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  contains all the methods for the neuron
 */
 
#include <iostream>
#include <random>
#include "neuron.hpp"


using namespace std;

/** Constructor
 *  needs a type (INHIBITORY or EXCITATORY) to set the specific J (the amplitude of the EPSP)
 *  @note the neuron is REFRACTORY by default
 *  @param type
 */
 
Neuron::Neuron(Type type)
	: localStep(0), type(type)
{

	state = REFRACTORY;
	v = v_res; //mV
	spikes.clear();
	ringBuffer.resize(D_step + 1);
	
	if(type == INHIBITORY){
		J = J_i;
	}
	
	if(type == EXCITATORY){
		J = J_e;
	}
}

/** update
 * 
 *  @param iExt	 the current given to the neuron
 *  @param simStep 	the time expressed in steps at which the neuron update
 *  @retval TRUE	the neuron spikes
 *  @retval FALSE	the neuron doesn't spike
 */

bool Neuron::update(double iExt, double simStep)
{
	bool isSpiking(false);
	
	updateState(localStep);
	
	if(state == ACTIVE) {


		// Distribution de poisson
		poisson_distribution<> poisson(2*v_th*C_e*h*J);
		random_device rd;
		mt19937 gen(rd());
		
		// Potentiel de la membrane
		double r(tau/c);
		int x(simStep);
		
		v = c1*v + c2*iExt*r + ringBuffer[x%(D_step+1)] + poisson(gen);
		
		// Réinitialisation de la cellule du ringBuffer qui vient d'être utilisée
		ringBuffer[x%(D_step+1)] = 0;
		
		// Spike (20mV)
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

/** updateState
 * 
 * @param simStep 	the time given in steps
 * @brief manage the switch between the ACTIVE and REFRACTORY state
 *   	  if the neurons spikes, it will be REFRACTORY for a certain time
 *   	  given by refractoryTime
 */
 
void Neuron::updateState(double simStep)
{
	if(spikes.empty() or abs(spikes.back() - (simStep))*h > refractoryTime) {
		state = ACTIVE;
	} else {
		state = REFRACTORY;
	}
	
}

/** getSpikesTime
 * 
 * @return spikes	the step when a spike occured
 */
 
vector<long> Neuron::getSpikesTime()
{
	return spikes;
}

/** getV
 * 
 * @return v 	the membrane potential of the neuron
 */

double Neuron::getV()
{
	return v;
}

/** getJ
 * 
 * @return J 	the amplitude of the EPSP (excitatory post synaptic potential)
 */

double Neuron::getJ()
{
	
	return J;
}


/** receive
 * 
 * @param step 	the step at which the neuron receive an EPSP from an other one
 * @param J 	the amplitude of the EPSP that is received
 * @brief put the ESPS received in the ringBuffer that manage the delay of the actual effect of the ESPS
 */
 
void Neuron::receive(long step, double J) 
{
	int x(step);
	ringBuffer[x%(D_step+1)] += J;
}
