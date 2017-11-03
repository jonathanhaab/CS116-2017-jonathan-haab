#include "neuron.hpp"
#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST (Neurontest, ExcitatoryImput1) {
	
	Neuron neuron(EXCITATORY);
	double imputCurrent(1.0);
	
	//Test after one update
	neuron.updateTest(imputCurrent, 1);
	EXPECT_EQ(c2*imputCurrent, neuron.getV());
	
	//Test after several update
	neuron.updateTest(imputCurrent, 10000);
	EXPECT_GT(1e-3, std::fabs(19.9999 - neuron.getV()));
	
}

TEST (Neurontest, ExcitatoryImput0) {
	
	Neuron neuron(EXCITATORY);
	double imputCurrent(0.0);
	
	neuron.updateTest(imputCurrent, 2000);

	EXPECT_NEAR(0, neuron.getV(), 1e-3);
	
}

TEST (Neurontest, ExcitatoryImput1_01) {
	
	Neuron neuron(EXCITATORY);
	double imputCurrent(1.01);
	
	//known spike times
	neuron.updateTest(imputCurrent, 923);
	EXPECT_NEAR(19.999, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 924);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 1867);
	EXPECT_NEAR(19.999, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 1868);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 2811);
	EXPECT_NEAR(19.999, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 2812);
	EXPECT_EQ(0, neuron.getV());
}

TEST (Neurontest, InhibitoryImput1) {
	
	Neuron neuron(INHIBITORY);
	double imputCurrent(1.0);
	
	//Test after one update
	neuron.updateTest(imputCurrent, 1);
	EXPECT_EQ(c2*imputCurrent, neuron.getV());
	
	//Test after several update
	neuron.updateTest(imputCurrent, 10000);
	EXPECT_GT(1e-3, std::fabs(19.9999 - neuron.getV()));
	
}

TEST (Neurontest, InhibitoryImput0) {
	
	Neuron neuron(INHIBITORY);
	double imputCurrent(0.0);
	
	neuron.updateTest(imputCurrent, 2000);

	EXPECT_NEAR(0, neuron.getV(), 1e-3);
	
}

TEST (Neurontest, InhibitoryImput1_01) {
	
	Neuron neuron(INHIBITORY);
	double imputCurrent(1.01);
	
	//known spike times
	neuron.updateTest(imputCurrent, 923);
	EXPECT_NEAR(19.999, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 924);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 1867);
	EXPECT_NEAR(19.999, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 1868);
	EXPECT_EQ(0, neuron.getV());
	
	neuron.updateTest(imputCurrent, 2811);
	EXPECT_NEAR(19.999, neuron.getV(), 1e-3);
	
	neuron.updateTest(imputCurrent, 2812);
	EXPECT_EQ(0, neuron.getV());
}

TEST (Neurontest, ExcitatoryConnexion1_01) {
	
	Neuron neuron1(EXCITATORY);
	Neuron neuron2(EXCITATORY);
	
	double imputCurrent(1.01);
	
	int spikeOnStep(924);
	
	neuron2.updateTest(0, spikeOnStep);
	
	if(neuron1.updateTest(imputCurrent, spikeOnStep)){

		neuron2.receive(spikeOnStep+1, neuron1.getJ());
	}
	
	
	for(int i(0); i < (spikeOnStep + bufferDelay); ++i){
		neuron2.updateTest(0, i);
		std::cout << neuron2.getV() << std::endl;
	}
	
	neuron2.updateTest(0, spikeOnStep + bufferDelay + 1);
	
	EXPECT_EQ(neuron2.getV(), neuron1.getJ());
	
}

