#pragma once
#include "Pilot.h"
#include "NeuralNet.h"

class NeuralPilot :	public Pilot
{
public:
	NeuralPilot ();
	NeuralPilot (Track *track, Car *car);
	~NeuralPilot ();

private:
	NeuralNet left_net;
	NeuralNet right_net;
	NeuralNet accelerate_net;
	NeuralNet brake_net;

	bool determine_left () override;
	bool determine_right () override;
	bool determine_accelerate () override;
	bool determine_brake () override;
};

