#include "stdafx.h"
#include "NeuralPilot.h"


NeuralPilot::NeuralPilot ()
{
}

NeuralPilot::NeuralPilot (Track * track, Car * car)
	:
	Pilot(track, car),
	left_net (5, 2),
	right_net (5, 2),
	accelerate_net (5, 2),
	brake_net (5, 2)
{

}

NeuralPilot::~NeuralPilot ()
{
}

bool NeuralPilot::determine_left ()
{
	float f = left_net.output (distances);

	return f > 0.5f;
}

bool NeuralPilot::determine_right ()
{
	float f = right_net.output (distances);

	return f > 0.5f;
}

bool NeuralPilot::determine_accelerate ()
{
	float f = accelerate_net.output (distances);

	return f > 0.5f;
}

bool NeuralPilot::determine_brake ()
{
	float f = brake_net.output (distances);

	return f > 0.5f;
}
