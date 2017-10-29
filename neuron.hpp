/**
 * @file   neuron.hpp
 * @Author Jonathan Haab 
 * @date   Automn, 2017
 * @brief  class that describe a neuron
 */
 
#include <iostream>
#include <vector>
#include <cmath>
#include "constants.hpp"
 
#ifndef NEURON_H
#define NEURON_H


enum State {ACTIVE, REFRACTORY, stateSize};
enum Type {INHIBITORY, EXCITATORY, typeSize};

class Neuron
{
	public :

		//Constructeur
		Neuron(Type type);
		
		// Update
		bool update(double iExt, double simStep);
		
		// Getter
		std::vector<long> getSpikesTime();
		double getV();
		double getJ();
		
		// Recoit un spike d'un autre neurone
		void receive(long step, double J);
		
		
	private :
	
		State state;
		Type type;
		double v; // Potentiel de dépolarisation
		double J; // Amplitude du EPSP (excitatory post synaptic potential)
		std::vector<long> spikes; // pour mémoriser la step de chaque spike , ON RECUPERE LE NB DE SPIKES GRACE A LA TAILLE DU VECTOR
		long localStep;
		
		std::vector<double> ringBuffer;
		
		void updateState(double simStep);
};



#endif
