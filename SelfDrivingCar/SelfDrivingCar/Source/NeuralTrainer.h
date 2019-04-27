#pragma once
#include "Updateable.h"
#include "NeuralPilot.h"
#include "Sensor.h"
#include "Circle.h"

class NeuralTrainer : public Updateable
{
public:
	NeuralTrainer (Track *track);
	~NeuralTrainer ();
	static double T;

	void update (const double &dt) override;

private: 
	const int max = 10;
	const bool training = false;
	const bool visualize = true;
	int iteration = 0;
	Track *track;
	Drawing::Rectangle *dot;
	float loaded_old[4] = { 0.1f, 0.7f, 0.0f, 0.2f };
	float loaded_new[4] = { 0.7f, 0.3f, 0.0f, 1.0f };
	float fresh[4] =	  { 0.1f, 0.1f, 0.5f, 1.0f };
	int current_state = initial_setup;
	enum state { initial_setup, init, driving, stepping, off };

	std::vector<NeuralPilot *> pilot_list;

	bool compare_fitness (const NeuralPilot& p1, const NeuralPilot& p2);

	struct compare_fitness_
	{
		inline bool operator()(const NeuralPilot *p1, const NeuralPilot *p2)
		{
			return p1->get_fitness(NeuralTrainer::T) > p2->get_fitness(NeuralTrainer::T);
		}
	};

	void draw_gradient_field (NeuralPilot *p);
};

