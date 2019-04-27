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
	std::vector<Vec2> points = track->get_point_list ();
	int z = 0;

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
				z = 9;
			}
			else if (i >= max/4 && i < max/4*3)
			{
				color = loaded_new;
				z = 10;
			}
			else if (i >= max/4*3 && i <= max)
			{
				color = fresh;
				z = 10;
			}
			else
			{
				color = Environment::green;
				z = 10;
			}

			Car *car = new Car (-1.0f, -0.3f, color);

			car->set_level (z);



			if (i < points.size ())
			{
				car->set_position (points[i]);
			}
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
			current_state = (int)off;
		}
		T = 0;

		break;
	case driving:
		T += dt;

		dot->visible (true);

		if (T >= 10)
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

			p1->random_step (-2);
			p2->random_step (2);

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
		//draw_gradient_field (pilot_list[0]);
		break;
	default:
		break;
	}
}

bool NeuralTrainer::compare_fitness (const NeuralPilot& p1, const NeuralPilot& p2)
{
	return p1.get_fitness (T) < p2.get_fitness (T);
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

			for (int i = 0; i < 12; ++i)
			{
				float distances[5];
				float phi = ((float)i/11) * 2 * 3.1415926535;
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
