#pragma once
#include "Updateable.h"
#include "Pilot.h"
#include "NeuralPilot.h"
#include "NeuralVisualization.h"
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
	enum fittnes_type { progression, laptime };
	enum variation_type { random_step, new_net };
	static const int max = 10;
	byte laps[max];
	const int fitness_calculation = laptime;
	const int net_variation = random_step;
	const int number_of_laps = 3;
	const bool training = false;
	const bool visualize = false;
	const bool random_parameter = false;
	const double simulation_period_time = 30;
	int iteration = 0;
	int number_of_unfinished_pilots = max;
	Track *track;
	Drawing::Rectangle *dot;
	float loaded_old[4] = { 0.1f, 0.7f, 0.0f, 0.2f };
	float loaded_new[4] = { 0.7f, 0.3f, 0.0f, 1.0f };
	float fresh[4] =	  { 0.1f, 0.1f, 0.5f, 1.0f };
	int current_state = initial_setup;
	enum state { initial_setup, init, driving, stepping, waiting, off };

	std::vector<NeuralPilot *> pilot_list;

	bool compare_fitness (const NeuralPilot& p1, const NeuralPilot& p2);

	struct compare_fitness_by_progress
	{
		inline bool operator()(const NeuralPilot *p1, const NeuralPilot *p2)
		{
			return p1->get_fitness(NeuralTrainer::T) > p2->get_fitness(NeuralTrainer::T);
		}
	};

	struct compare_fitness_by_laptime
	{
		inline bool operator()(const NeuralPilot *p1, const NeuralPilot *p2)
		{
			return p1->get_fitness2 () < p2->get_fitness2 ();
		}
	};

	static void lap_finished_callback (void* NeuralTrainer, int hint, Pilot &pilot, int lap_counter);
	void lap_finished (Pilot &p, int hint, int lap_counter);

	static void crashed_callback (void* NeuralTrainer, int hint, Pilot &pilot);
	void crashed (Pilot &p, int hint);
	

	void draw_gradient_field (NeuralPilot *p);
};

