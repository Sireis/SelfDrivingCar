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
	static int space = 0;
	int count = 0;
	int error = 0;
	std::vector<Vec2> points = track->get_point_list ();
	int z = 0;

	if (glfwGetKey (Environment::window, GLFW_KEY_SPACE) == GLFW_RELEASE)
	{
		space = 0;
	}

	if (glfwGetKey (Environment::window, GLFW_KEY_SPACE) == GLFW_PRESS && space == 0 && current_state != waiting)
	{
		space = 1;

		for (int i = 0; i < pilot_list.size (); ++i)
		{
			pilot_list[i]->do_updates (false);
		}

		current_state = waiting;
	}

	switch (current_state)
	{
	case initial_setup:
		dot = new Drawing::Rectangle (Vec2 (-1.5,-0.80), Vec2 (0.15, 0.15), Environment::green);
		dot->visible (false);

		for (int i = 0; i < max; ++i)
		{
			laps[i] = 0;
		}

		for (int i = 0; i < max; ++i)
		{
			std::string s = "..\\Nets\\";
			s += std::to_string (i) + "\\2.net";
			std::ifstream f (s);
			s = "..\\Nets\\" + std::to_string (i);

			const float *color;

			if (i >= 0 && i < max / 4)
			{
				color = loaded_old;
				z = 9;
			}
			else if (i >= max / 4 && i < max / 4 * 3)
			{
				color = loaded_new;
				z = 10;
			}
			else if (i >= max / 4 * 3 && i <= max)
			{
				color = fresh;
				z = 10;
			}
			else
			{
				color = Environment::green;
				z = 10;
			}

			Car *car = new Car (track->get_start(), color);
			car->set_level (z);

			NeuralPilot *pilot = new NeuralPilot (track, car);

			if (fitness_calculation == laptime)
			{
				pilot->register_crashed (NeuralTrainer::crashed_callback, this, i);
			}
			pilot->register_lap_finished (NeuralTrainer::lap_finished_callback, this, i);

			if (f.good ())
			{
				pilot->load_nets_from_file (s);
			}
			else
			{
				if (training && !random_parameter)
				{
					pilot->do_drive (false);
				}
			}

			pilot_list.push_back (pilot);

			if (i == 2501)
			{
				pilot->plot_parameter ();
			}
		}

		if (visualize)
		{
			draw_gradient_field (pilot_list[0]);
		}

		if (training)
		{
			current_state = (int)driving;
		}
		else
		{
			new NeuralVisualization (Vec2 (-1.7, +0.2), &(pilot_list[0]->get_left_net ()));
			new NeuralVisualization (Vec2 (-1.7, -0.2), &(pilot_list[0]->get_right_net ()));
			new NeuralVisualization (Vec2 (-1.7, -0.6), &(pilot_list[0]->get_accelerate_net ()));

			current_state = (int)off;
		}

		break;
	case init:
		number_of_unfinished_pilots = max;
		for (int i = 0; i < max; ++i)
		{
			laps[i] = 0;
		}
		
		for (int i = 0; i < max && i < pilot_list.size (); ++i)
		{
			pilot_list[i]->reset ();
		}

		T = 0;
		current_state = (int)driving;
		break;
	case driving:
		T += dt;

		dot->visible (true);

		
		if ((fitness_calculation == progression && T >= simulation_period_time)
			|| (fitness_calculation == laptime && number_of_unfinished_pilots <= max /4 * 3))
		{
			dot->visible (false);
			current_state = (int)stepping; 
		}

		break;
	case stepping:
		iteration++;
		if (fitness_calculation == progression)
		{
			std::sort (pilot_list.begin (), pilot_list.end (), compare_fitness_by_progress ());
		}
		else if (fitness_calculation == laptime)
		{
			std::sort (pilot_list.begin (), pilot_list.end (), compare_fitness_by_laptime ());
		}

		std::cout << "ITERATION " << iteration << " -----------------------" << std::endl;

		if (!RemoveDirectory ("..\\Nets"))
		{
			error = GetLastError ();
		}
		CreateDirectory ("..\\Nets", NULL);


		for (int i = 0; i < max / 4 && i < pilot_list.size(); ++i)
		{
			int index_left = 2 * i + pilot_list.size () / 4;
			int index_right = 2 * i + pilot_list.size () / 4 + 1;
			std::string s = "..\\Nets\\";
			std::string s0 = s + std::to_string (i);
			std::string s1 = s + std::to_string (2 * i + pilot_list.size()/4);
			std::string s2 = s + std::to_string (2 * i + pilot_list.size()/4 + 1);
			
			CreateDirectory (s0.c_str (), NULL);
			CreateDirectory (s1.c_str (), NULL);
			CreateDirectory (s2.c_str (), NULL);
			pilot_list[i]->save_nets_to_file (s0);

			//NeuralPilot *p = new NeuralPilot (pilot_list[index], pilot_list[index - 1]);
			NeuralPilot *p1 = new NeuralPilot (*pilot_list[i]);
			p1->give_new_car (new Car (track->get_start(),loaded_new));
			NeuralPilot *p2 = new NeuralPilot (*pilot_list[i]);
			p2->give_new_car (new Car (track->get_start (), loaded_new));

			switch (net_variation)
			{
			case random_step:
				p1->random_step (-1);
				p2->random_step (1);
				break;
			case new_net:
				p1->new_net (2);
				p2->new_net (2);
			}

			p1->save_nets_to_file (s1);
			pilot_list[index_left]->dispose ();
			pilot_list[index_left] = p1;

			p2->save_nets_to_file (s2);
			pilot_list[index_right]->dispose ();
			pilot_list[index_right] = p2;
		}
		for (int i = max / 4 * 3; i < max && i < pilot_list.size(); ++i)
		{
			pilot_list[i]->dispose ();
			count++;
		}
		for (int i = 0; i < count; ++i)
		{
			pilot_list.pop_back ();
		}
		for (int i = pilot_list.size() - 1; i >= 0 ; --i)
		{
			float f;
			fitness_calculation == progression ? f = pilot_list[i]->get_fitness (T) : f = f;
			fitness_calculation == laptime ? f = pilot_list[i]->get_fitness2 () : f = f;
			std::cout << "Fitness of " << i << ": " << f << std::endl;
		}
		current_state = (int)init;

		break;
	case off:
		//draw_gradient_field (pilot_list[0]);
		break;

	case waiting:
		if (glfwGetKey (Environment::window, GLFW_KEY_SPACE) == GLFW_PRESS && space == 0)
		{
			space = 1;
			
			for (int i = 0; i < pilot_list.size (); ++i)
			{
				pilot_list[i]->do_updates (true);
			}

			current_state = driving;
		}

		break;
	default:
		break;
	}
}

bool NeuralTrainer::compare_fitness (const NeuralPilot& p1, const NeuralPilot& p2)
{
	return p1.get_fitness (T) < p2.get_fitness (T);
}

void NeuralTrainer::lap_finished_callback (void * trainer, int hint, Pilot & pilot, int lap_counter)
{
	NeuralTrainer *self = static_cast<NeuralTrainer*>(trainer);
	self->lap_finished (pilot, hint, lap_counter);
}

void NeuralTrainer::lap_finished (Pilot & p, int hint, int lap_counter)
{
	if (training && fitness_calculation == laptime)
	{
		laps[hint]++;
		if (laps[hint] >= number_of_laps)
		{
			number_of_unfinished_pilots--;
			p.do_drive (false);
		}
	}
	else
	{
		std::cout << "Some pilot finished lap in " << p.get_laptime () << "s." << std::endl;;
	}
}

void NeuralTrainer::crashed_callback (void * trainer, int hint, Pilot & pilot)
{
	NeuralTrainer *self = static_cast<NeuralTrainer*>(trainer);
	self->crashed (pilot, hint);
}

void NeuralTrainer::crashed (Pilot & p, int hint)
{
	//number_of_unfinished_pilots--;
	p.do_drive (false);
}

void NeuralTrainer::draw_gradient_field (NeuralPilot * p)
{
	std::vector<Wall *> walls = track->get_wall_list ();
	Sensor *sensor = new Sensor ();
	const float *color = Environment::black;
	Vec2 probe, a, b;

	float ar = Environment::aspect_ratio;

	float width = 0.013;

#define ALL
#ifdef ALL
	for (float x = -1.0 / ar; x < 1.0 / ar; x += width*2.5)
	{
		for (float y = -1.0; y < 1.0; y += width*2.5)
		{
			probe = Vec2 (x, y);
			Drawing::Circle *dot = new Drawing::Circle (probe, width, Environment::white);
			dot->set_level (-1);

			for (int i = 0; i < 15; ++i)
			{
				float distances[5];
				float phi = ((float)i/15) * 2 * 3.1415926535;
				sensor->set_position (probe);
				sensor->rotate (phi);
				sensor->get_distances (track, distances);

				bool l = p->tell_left (distances);
				bool r = p->tell_right (distances);

				if (l == r)
				{
					color = Environment::white;
				}
				else if (l)
				{
					color = Environment::red;
				}
				else if (r)
				{
					color = Environment::green;
				}

				dot->set_color (phi, color);
			}
		}
	}
#else
	for (int i = 0; i < walls.size (); i += 2)
	{
		for (int j = 0; j < 15; ++j)
		{
			float distances[5];
			a = walls[i]->get_start (); b = walls[i + 1]->get_start();
			probe = a + (b - a).normalize () * (0.3 * j / 15);

			sensor->set_position (probe);
			sensor->get_distances (track, distances);

			bool l = p->tell_left (distances);
			bool r = p->tell_right (distances);

			if (l == r)
			{
				color = Environment::white;
			}
			else if (l)
			{
				color = Environment::red;
			}
			else if (r)
			{
				color = Environment::green;
			}

			Drawing::Circle *dot = new Drawing::Circle (probe, width, color);
			dot->set_level (-1);
		}
	}
#endif

	//for (int i = 0; i < walls.size ()/2; ++i)
	//{
	//	Vec2 a = walls[2*i]->get_start ();
	//	Vec2 b = walls[2*i+1]->get_start ();

	//	for (int j = 0; j < 10; ++j)
	//	{
	//		Vec2 c = a + (b - a) / 10 * i;

	//		probe->set_position (c);
	//		if (p->tell_left () == p->tell_right ())
	//		{
	//			color = Environment::white;
	//		}
	//		else if (p->tell_left ())
	//		{
	//			color = Environment::red;
	//		}
	//		else if (p->tell_right ())
	//		{
	//			color = Environment::green;
	//		}

	//		Drawing::Rectangle *dot = new Drawing::Rectangle (c, Vec2 (0.02, 0.02), color);
	//	}
	//}
}


