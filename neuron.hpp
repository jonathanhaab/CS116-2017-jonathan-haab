#include <iostream>
#include <vector>
#include <cmath>
 
#ifndef NEURON_H
#define NEURON_H


enum State { EXCITATORY, INHIBITORY, REFRACTORY , stateSize};


class Neuron
{
	public :
	
		static constexpr double h = 0.1;
		static constexpr long tau = 20; //ms
		static constexpr double tau_ref = 2; //ms
		static constexpr double refractoryTime = 2.0;
		static constexpr double v_th = 20; //mV
		static constexpr double v_res = 0;
		
		static constexpr double c = 1;
		static constexpr double R = 20e6; // 20.0 G ohm résistance de la membrane
		static constexpr int D_step = 15;
		static constexpr double c1 = exp(-h/tau);
		static constexpr double c2 = 1-exp(-h/tau);
	
		//Constructeur
		Neuron();
		
		// Update
		bool update(double iExt, double simStep);
		
		
		// Getter
		std::vector<long> getSpikesTime();
		double getV();
		double getJ();
		
		
		// Recoit un spike d'un autre neurone
		void receive(long step, double J);
		
		//Constantes
		/*
		static const double neuron_number = 0; /// à changer
		static const double excitatory_number = 0.8*neuron_number;
		static const double inhibitory_number = 0.2*neuron_number;
		
		
		static const double gamma = 0.25; /// à changer
		static const double excitatory_c = 1; /// à changer
		static const double inhibitory_c = gamma*excitatory_c;
		static const double exterior_c = excitatory_c;
		*/
		

		
		
	private :
	
		State state;
		double v; // Potentiel de dépolarisation
		const double J; // Amplitude du EPSP (excitatory post synaptic potential)
		std::vector<long> spikes; // pour mémoriser la step de chaque spike , ON RECUPERE LE NB DE SPIKES GRACE A LA TAILLE DU VECTOR
		long localStep;
		
		std::vector<double> ringBuffer;
		
		//double c; // Connections reçues par le neurone
		
		void updateState(double simStep);
		
};

/*
	static const double Neuron::neuron_number(0); /// à changer
	static const double Neuron::excitatory_number(0.8*neuron_number);
	static const double Neuron::inhibitory_number(0.2*neuron_number;
	
	static const double Neuron::gamma(0.25); /// à changer
	static const double Neuron::excitatory_c(1); /// à changer
	static const double Neuron::inhibitory_c(gamma*excitatory_c);
	static const double Neuron::exterior_c(excitatory_c);
	
	static const long Neuron::tau(20); //ms
	static const double Neuron::tau_ref(2); //ms
	static const double Neuron::refractoryTime(2.0);
	static const double Neuron::v_th(20); mV
	static const double Neuron::v_res(10);
*/

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
