#pragma once
#include "Pilot.h"
#include "NeuralNet.h"

class NeuralPilot :	public Pilot
{
public:
	NeuralPilot ();
	NeuralPilot (Track *track, Car *car);
	NeuralPilot (NeuralPilot *n1, NeuralPilot *n2);
	~NeuralPilot ();

	void load_nets_from_file (std::string path_to_root);
	void save_nets_to_file (std::string path_to_root);

	float get_fitness (double dt) const;

	void random_step (int factor);

	void plot_parameter ();


	bool tell_left (float* distances);
	bool tell_right (float* distances);

	NeuralNet& get_left_net ();
	NeuralNet& get_right_net ();
	NeuralNet& get_accelerate_net ();
	NeuralNet& get_brake_net ();

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

