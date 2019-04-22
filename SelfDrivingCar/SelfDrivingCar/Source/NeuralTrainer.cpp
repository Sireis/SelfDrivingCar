#include "stdafx.h"
#include "NeuralTrainer.h"

double NeuralTrainer::T = 0;

NeuralTrainer::NeuralTrainer (Track *track)
	:
	track(track)
{
}


NeuralTrainer::~NeuralTrainer ()
{
}

void NeuralTrainer::update (const double & dt)
{
	int error = 0;
	switch (current_state)
	{
	case initial_setup:
		dot = new Drawing::Rectangle (Vec2 (-1.5,-0.80), Vec2 (0.15, 0.15), Environment::green);
		dot->visible (false);

		current_state = (int)init;
		break;
	case init:
		for (int i = 0; i < max; ++i)
		{
			std::string s = "Nets\\";
			s += std::to_string(i) + "\\3.net";
			std::ifstream f (s);
			s = "Nets\\" + std::to_string (i);

			const float *color;

			if (i >= 0 && i < max/4)
			{
				color = loaded_old;
			}
			else if (i >= max/4 && i < max/4*3)
			{
				color = loaded_new;
			}
			else if (i >= max/4*3 && i <= max)
			{
				color = fresh;
			}
			else
			{
				color = Environment::green;
			}

			Car *car = new Car (-1.0f, -0.3f, color);
			NeuralPilot *pilot = new NeuralPilot (track, car);

			if (f.good ())
			{
				pilot->load_nets_from_file (s);			
			}

			pilot_list.push_back (pilot);

			if (i == 0)
			{
				pilot->plot_parameter ();
			}
		}

		current_state = (int)driving;
		T = 0;

		break;
	case driving:
		T += dt;

		dot->visible (true);

		if (T >= 5)
		{
			dot->visible (false);
			current_state = (int)stepping;
		}

		break;
	case stepping:
		iteration++;
		std::sort (pilot_list.begin (), pilot_list.end (), compare_fitness_());

		std::cout << "ITERATION " << iteration << " -----------------------" << std::endl;

		if (!RemoveDirectory ("Nets"))
		{
			error = GetLastError ();
		}
		CreateDirectory ("Nets", NULL);


		for (int i = 0; i < pilot_list.size () / 4; ++i)
		{
			std::string s = "Nets\\";
			std::string s1 = s + std::to_string (2 * i + pilot_list.size()/4);
			std::string s2 = s + std::to_string (2 * i + pilot_list.size()/4 + 1);
			
			CreateDirectory (s1.c_str (), NULL);
			CreateDirectory (s2.c_str (), NULL);

			//NeuralPilot *p = new NeuralPilot (pilot_list[index], pilot_list[index - 1]);
			NeuralPilot *p1 = new NeuralPilot (*pilot_list[i]);
			NeuralPilot *p2 = new NeuralPilot (*pilot_list[i]);

			p1->random_step (-1);
			p2->random_step (1);

			p1->save_nets_to_file (s1);
			p1->dispose ();
			p2->save_nets_to_file (s2);
			p2->dispose ();
		}
		for (int i = 0; i < pilot_list.size () / 4; ++i)
		{
			std::string s = "Nets\\";
			s += std::to_string (i);
			CreateDirectory (s.c_str(), NULL);
			pilot_list[i]->save_nets_to_file (s);
		}
		for (int i = pilot_list.size() - 1; i >= 0 ; --i)
		{
			float f = pilot_list[i]->get_fitness (T);
			std::cout << "Fitness of " << i << ": " << f << std::endl;
			pilot_list[i]->dispose ();
		}
		pilot_list.clear ();
		current_state = (int)init;

		break;
	case off:
		break;
	default:
		break;
	}
}

bool NeuralTrainer::compare_fitness (const NeuralPilot& p1, const NeuralPilot& p2)
{
	return p1.get_fitness (T) < p2.get_fitness (T);
}
