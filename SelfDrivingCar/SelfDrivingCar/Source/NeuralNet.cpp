#include "stdafx.h"
#include "NeuralNet.h"


NeuralNet::NeuralNet ()
{
}

NeuralNet::NeuralNet (const int input_count, const int number_of_layers)
	:
	input_count(input_count),
	number_of_layers(number_of_layers)
{
	weights = new Eigen::MatrixXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		weights[i] = Eigen::MatrixXf (input_count, input_count);

		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				weights[i] (j, k) = ((float) (rand () % 100) / (float) 100) - 0.5f;
			}
		}
	}

	biases = new Eigen::VectorXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		biases[i] = Eigen::VectorXf (input_count);

		for (int j = 0; j < input_count; ++j)
		{
			biases[i] (j) = ((float)(rand () % 100) / (float)100) - 0.5f;
		}
	}

	last_weights = new float[input_count];

	for (int i = 0; i < input_count; ++i)
	{
		last_weights[i] = ((float)(rand () % 100) / (float)100) - 0.5f;
	}

	last_bias = ((float)(rand () % 100) / (float)100) - 0.5f;

	u = Eigen::VectorXf (input_count);
	temp = Eigen::VectorXf (input_count);
	one = Eigen::VectorXf (input_count);
	one.fill (1.0f);
}

float NeuralNet::output (const float *inputs)
{
	for (int i = 0; i < input_count; ++i)
	{
		u (i) = inputs[i];
	}

	for (int i = 0; i < number_of_layers; ++i)
	{
		u = weights[i] * u - biases[i];
		u = logistic_function (u);
	}	

	float f = 0.0f;
	for (int i = 0; i < input_count; ++i)
	{
		f += last_weights[i] * u (i);
	}
	f -= last_bias;
	f = 1 / (1 + exp (-f));

	return f;
}

void NeuralNet::save_to_file (std::string path_to_file)
{
	std::ofstream file;
	file.open (path_to_file, std::ios::binary);

	int n_int = sizeof (int);
	int n_float = sizeof (float);
	int total_size =
		n_int * 2 +
		n_float * (input_count * input_count * number_of_layers + input_count * number_of_layers) +
		n_float * (input_count + 1);

	char *buffer = new char[total_size];

	char * ptr = buffer;

	memcpy (buffer, (void *)&input_count, n_int);
	buffer += n_int;
	memcpy (buffer, (void *)&number_of_layers, n_int);
	buffer += n_int;

	for (int i = 0; i < number_of_layers; ++i)
	{
		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				memcpy (buffer, (void *)&weights[i] (j, k), n_float);
				buffer += n_float;
			}
		}
	}

	for (int i = 0; i < number_of_layers; ++i)
	{
		for (int j = 0; j < input_count; ++j)
		{
			memcpy (buffer, (void *)&biases[i] (j), n_float);
			buffer += n_float;
		}
	}

	for (int i = 0; i < input_count; ++i)
	{
		memcpy (buffer, (void *)&last_weights[i], n_float);
		buffer += n_float;
	}

	memcpy (buffer, (void *)&last_bias, n_float);

	file.write (ptr, total_size);
}

void NeuralNet::load_from_file (std::string path_to_file)
{
	std::ifstream file;
	file.open (path_to_file, std::ios::binary);

	int size = file.tellg ();
	char *buffer = new char[size];
	file.read (buffer, size);

	int n_int = sizeof (int);
	int n_float = sizeof (float);

	float tmp;

	memcpy ((void *)&input_count, buffer, n_int);
	buffer += n_int;
	memcpy ((void *)&number_of_layers, buffer, n_int);
	buffer += n_int;

	weights = new Eigen::MatrixXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		weights[i] = Eigen::MatrixXf (input_count, input_count);

		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				memcpy ((void *)&tmp, buffer, n_float);
				buffer += n_float;
				weights[i] (j, k) = tmp;
			}
		}
	}

	biases = new Eigen::VectorXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		biases[i] = Eigen::VectorXf (input_count);

		for (int j = 0; j < input_count; ++j)
		{
			memcpy ((void *)&tmp, buffer, n_float);
			buffer += n_float;
			biases[i] (j) = tmp;
		}
	}

	last_weights = new float[input_count];

	for (int i = 0; i < input_count; ++i)
	{
		memcpy ((void *)&tmp, buffer, n_float);
		buffer += n_float;
		last_weights[i] = tmp;
	}
	
	memcpy ((void *)&last_bias, buffer, n_float);
	buffer += n_float;

	u = Eigen::VectorXf (input_count);
	temp = Eigen::VectorXf (input_count);
	one = Eigen::VectorXf (input_count);
	one.fill (1.0f);
}

Eigen::VectorXf NeuralNet::logistic_function (Eigen::VectorXf u)
{
	u = -1 * u;
	u = u.array ().exp ();
	u = u + one;
	u = u.cwiseInverse ();
	return u;
}

NeuralNet::NeuralNet (std::string path_to_file)
{
	load_from_file (path_to_file);
}

NeuralNet::~NeuralNet ()
{
}
