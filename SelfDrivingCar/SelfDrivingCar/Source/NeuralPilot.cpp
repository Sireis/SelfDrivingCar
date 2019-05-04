#include "stdafx.h"
#include "NeuralPilot.h"


NeuralPilot::NeuralPilot ()
{
}

NeuralPilot::NeuralPilot (Track * track, Car * car)
	:
	Pilot(track, car),
	left_net (5, 1),
	right_net (5, 1),
	accelerate_net (6, 1)
{

}

NeuralPilot::NeuralPilot (NeuralPilot * n1, NeuralPilot * n2)
	:
	left_net (n1->get_left_net (), n2->get_left_net()),
	right_net (n1->get_right_net (), n2->get_right_net ()),
	accelerate_net (n1->get_accelerate_net (), n2->get_accelerate_net ())
{
}

NeuralPilot::~NeuralPilot ()
{
}

void NeuralPilot::load_nets_from_file (std::string path_to_root)
{
	left_net.load_from_file (path_to_root + "\\0.net");
	right_net.load_from_file (path_to_root + "\\1.net");
	accelerate_net.load_from_file (path_to_root + "\\2.net");
}

void NeuralPilot::save_nets_to_file (std::string path_to_root)
{
	left_net.save_to_file (path_to_root + "\\0.net");
	right_net.save_to_file (path_to_root + "\\1.net");
	accelerate_net.save_to_file (path_to_root + "\\2.net");
}

float NeuralPilot::get_fitness (double dt) const
{	
	if (going_forward)
	{
		return (index_now + 100 * lap_counter) / dt;
	}
	else
	{
		return -1.0f;
	}
}

float NeuralPilot::get_fitness2 () const
{
	if (going_forward)
	{
		return lap_time;
	}
	else
	{
		return -1.0f;
	}
}

void NeuralPilot::random_step (int factor)
{
	int r = rand () % 3;

	switch (r)
	{
	case 0:
		left_net.random_step (factor);
		break;
	case 1:
		right_net.random_step (factor);
		break;
	case 2:
		accelerate_net.random_step (factor);
		break;
	default:
		break;
	}
	//brake_net.random_step (factor);
}

void NeuralPilot::new_net (int net_id)
{
	int a, b;
	switch (net_id)
	{
	case 0:
		a = left_net.get_input_count();
		b = left_net.get_number_of_layers();
		left_net = NeuralNet (a,b);
		break;
	case 1:
		a = right_net.get_input_count();
		b = right_net.get_number_of_layers();
		right_net = NeuralNet (a, b);
		break;
	case 2:
		a = accelerate_net.get_input_count();
		b = accelerate_net.get_number_of_layers();
		accelerate_net = NeuralNet (a, b);
		break;
	default:
		break;
	}
}

void NeuralPilot::plot_parameter ()
{
	//left_net.plot_net ();
	//right_net.plot_net ();
	accelerate_net.plot_net ();
}

bool NeuralPilot::tell_left (float* distances)
{
	float tmp[5];

	for (int i = 0; i < 5; ++i)
	{
		tmp[i] = this->distances[i];
		this->distances[i] = distances[i];
	}

	float f = determine_left ();

	for (int i = 0; i < 5; ++i)
	{
		this->distances[i] = tmp[i];
	}

	return f;
}

bool NeuralPilot::tell_right (float* distances)
{
	float tmp[5];

	for (int i = 0; i < 5; ++i)
	{
		tmp[i] = this->distances[i];
		this->distances[i] = distances[i];
	}

	float f = determine_right ();

	for (int i = 0; i < 5; ++i)
	{
		this->distances[i] = tmp[i];
	}

	return f;
}

NeuralNet & NeuralPilot::get_left_net ()
{
	return left_net;
}

NeuralNet & NeuralPilot::get_right_net ()
{
	return right_net;
}

NeuralNet & NeuralPilot::get_accelerate_net ()
{
	return accelerate_net;
}

bool NeuralPilot::determine_left ()
{
	float l = left_net.output (distances);
	float r = right_net.output (distances);

	return l > 0.5f && l > r;
}

bool NeuralPilot::determine_right ()
{
	float l = left_net.output (distances);
	float r = right_net.output (distances);

	return r > 0.5f && r > l;
}

bool NeuralPilot::determine_accelerate ()
{
	float f = accelerate_net.output (distances);

	return f > 0.5f;
}

bool NeuralPilot::determine_brake ()
{
	//float f = brake_net.output (distances);

	//return f > 0.5f;
	return false;
}
