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
	switch (current_state)
	{
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
				color = loaded_new;
			}
			else if (i >= max/4 && i < max/2)
			{
				color = fresh;
			}
			else if (i >= max/2 && i <= max)
			{
				color = loaded_old;
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
		}

		current_state = (int)driving;
		T = 0;

		break;
	case driving:
		T += dt;

		if (T >= 5)
		{
			current_state = (int)stepping;
		}

		break;
	case stepping:
		iteration++;
		std::sort (pilot_list.begin (), pilot_list.end (), compare_fitness_());

		std::cout << "ITERATION " << iteration << " -----------------------" << std::endl;

		RemoveDirectory ("Nets");
		CreateDirectory ("Nets", NULL);


		for (int i = 0; i < pilot_list.size () / 4; ++i)
		{
			std::string s = "Nets\\";
			s += std::to_string (i);
			CreateDirectory (s.c_str (), NULL);

			int index = pilot_list.size () - i - 1;
			NeuralPilot *p = new NeuralPilot (pilot_list[index], pilot_list[index - 1]);

			p->save_nets_to_file (s);
			p->dispose ();
		}
		for (int i = pilot_list.size()/2; i < pilot_list.size (); ++i)
		{
			std::string s = "Nets\\";
			s += std::to_string (i);
			CreateDirectory (s.c_str(), NULL);
			pilot_list[i]->save_nets_to_file (s);
		}
		for (int i = 0; i < pilot_list.size(); ++i)
		{
			float f = pilot_list[i]->get_fitness (T);
			std::cout << "Fitness of " << i << ": " << f << std::endl;
			pilot_list[i]->dispose ();
		}
		pilot_list.clear ();
		current_state = (int)init;

		break;
	case off:
	default:
		break;
	}
}

bool NeuralTrainer::compare_fitness (const NeuralPilot& p1, const NeuralPilot& p2)
{
	return p1.get_fitness (T) < p2.get_fitness (T);
}
