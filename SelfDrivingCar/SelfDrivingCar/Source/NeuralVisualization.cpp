#include "stdafx.h"
#include "NeuralVisualization.h"


NeuralVisualization::NeuralVisualization (Vec2 position, NeuralNet * net)
	:
	net (net)
{
	float spacing_x = 0.17, spacing_y = 0.07, radius = 0.03;
	anchor = new Drawing::Rectangle (position, Vec2 (0.00, 0.00), Environment::transparent);	

	inputs = new Drawing::Circle*[net->get_input_count ()];

	for (int i = 0; i < net->get_input_count (); ++i)
	{
		inputs[i] = new Drawing::Circle (Vec2 (0, i*-spacing_y), radius, Environment::black, anchor);
	}

	biases = new Drawing::Circle*[net->get_input_count () * net->get_number_of_layers ()];

	for (int i = 0; i < net->get_number_of_layers (); ++i)
	{
		for (int j = 0; j < net->get_input_count(); ++j)
		{
			int index = i * net->get_input_count () + j;
			biases[index] = new Drawing::Circle (Vec2 (i*spacing_x + spacing_x, j*-spacing_y), radius, Environment::black, anchor);
		}
	}

	Vec2 last_bias_position = Vec2 ((net->get_number_of_layers () + 1)*spacing_x,((float) net->get_input_count() - 1)/2*-spacing_y);
	last_bias = new Drawing::Circle (last_bias_position, radius, Environment::black, anchor);


	weights = new Drawing::Rectangle*[net->get_input_count ()*net->get_input_count ()*net->get_number_of_layers ()];

	for (int i = 0; i < net->get_number_of_layers (); ++i)
	{
		for (int j = 0; j < net->get_input_count (); ++j)
		{
			for (int k = 0; k < net->get_input_count (); ++k)
			{
				int index = (i * net->get_input_count() *net->get_input_count()) + (j * net->get_input_count ()) + k;
				float f[2];
				inputs[j]->get_middle (f);
				Vec2 a = Vec2 (f[0], f[1]);
				biases[k]->get_middle (f);
				Vec2 b = Vec2 (f[0], f[1]);
				weights[index] = new Drawing::Rectangle (a + (b - a) / 2, Vec2 (0.005, (b - a).abs ()), Environment::white, anchor);
				weights[index]->rotate ((b - a).angle ());
			}
		}
	}

	for (int i = 0; i < net->get_number_of_layers () - 1; ++i)
	{

	}

	last_weights = new Drawing::Rectangle*[net->get_input_count ()];

	for (int i = 0; i < net->get_input_count (); ++i)
	{
		int index = (net->get_number_of_layers () - 1) * net->get_input_count () + i;
		float f[2];
		biases[index]->get_middle (f);
		Vec2 a = Vec2 (f[0], f[1]);
		last_bias->get_middle (f);
		Vec2 b = Vec2 (f[0], f[1]);
		last_weights[i] = new Drawing::Rectangle (a + (b - a) / 2, Vec2 (0.005, (b - a).abs ()), Environment::white, anchor);
		last_weights[i]->rotate ((b - a).angle ());
	}
}

NeuralVisualization::~NeuralVisualization ()
{
}

void NeuralVisualization::update (const double & dt)
{
	const float* color;

	for (int i = 0; i < net->get_number_of_layers (); ++i)
	{
		for (int j = 0; j < net->get_input_count (); ++j)
		{
			for (int k = 0; k < net->get_input_count(); k++)
			{
				int index = (i * net->get_input_count () * net->get_input_count ()) + (j * net->get_input_count ()) + k;
				float w = net->get_weights ()[i] (j, k);
				w < 0 ? color = Environment::red : color = Environment::white;
				w > 0 ? color = Environment::green : color = color;
				w = abs (w);
				w = 0.15f*(1.0f / (1.0f + expf (-w)) - 0.490);
				Vec2 s = Vec2 (w, weights[index]->get_size().y);
				weights[index]->set_size (s);
				weights[index]->set_color (color);
			}
		}
	}

	for (int i = 0; i < net->get_input_count (); ++i)
	{
		float w = net->get_last_weights()[i];
		w < 0 ? color = Environment::red : color = Environment::white;
		w > 0 ? color = Environment::green : color = color;
		w = abs (w);
		w = 0.15f*(1.0f / (1.0f + expf (-w)) - 0.490);
		Vec2 s = Vec2 (w, last_weights[i]->get_size ().y);
		last_weights[i]->set_size (s);
		last_weights[i]->set_color (color);
	}

	for (int i = 0; i < net->get_number_of_layers(); ++i)
	{
		for (int j = 0; j < net->get_input_count (); ++j)
		{
			int index = (i * net->get_input_count () + j);
			float w = net->get_biases ()[i] (j);
			w < 0 ? color = Environment::dark_red : color = Environment::white;
			w > 0 ? color = Environment::dark_green : color = color;
			biases[index]->Drawable::set_color (color);
		}
	}
	
	float w = net->get_last_bias ();
	w < 0 ? color = Environment::dark_red : color = Environment::white;
	w > 0 ? color = Environment::dark_green : color = color;
	last_bias->Drawable::set_color (color);
}
