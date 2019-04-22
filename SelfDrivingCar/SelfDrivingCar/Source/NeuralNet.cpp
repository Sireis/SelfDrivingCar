#include "stdafx.h"
#include "NeuralNet.h"


NeuralNet::NeuralNet ()
{
}

void NeuralNet::init ()
{
	weights = new Eigen::MatrixXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		weights[i] = Eigen::MatrixXf (input_count, input_count);

		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				weights[i] (j, k) = ((float)(rand () % 100) / (float)100) - 0.5f;
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

NeuralNet::NeuralNet (const int input_count, const int number_of_layers)
	:
	input_count(input_count),
	number_of_layers(number_of_layers)
{
	init ();
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
	char *ptr = buffer;

	memcpy (ptr, (void *)&input_count, n_int);
	ptr += n_int;
	memcpy (ptr, (void *)&number_of_layers, n_int);
	ptr += n_int;

	for (int i = 0; i < number_of_layers; ++i)
	{
		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				float f = weights[i] (j, k);
				memcpy (ptr, (void *)&f, n_float);
				ptr += n_float;
			}
		}
	}

	for (int i = 0; i < number_of_layers; ++i)
	{
		for (int j = 0; j < input_count; ++j)
		{
			memcpy (ptr, (void *)&biases[i] (j), n_float);
			ptr += n_float;
		}
	}

	for (int i = 0; i < input_count; ++i)
	{
		memcpy (ptr, (void *)&last_weights[i], n_float);
		ptr += n_float;
	}

	memcpy (ptr, (void *)&last_bias, n_float);

	file.write (buffer, total_size);
	file.close ();
	delete[] buffer;
}

void NeuralNet::load_from_file (std::string path_to_file)
{
	std::ifstream file;
	file.open (path_to_file, std::ios::binary);

	int begin = file.tellg ();
	file.seekg (0, std::ios::end);
	int size = file.tellg ();
	char *buffer = new char[size];
	char *ptr = buffer;
	file.seekg (0, std::ios::beg);
	file.read (buffer, size);

	int n_int = sizeof (int);
	int n_float = sizeof (float);

	float tmp;

	memcpy ((void *)&input_count, ptr, n_int);
	ptr += n_int;
	memcpy ((void *)&number_of_layers, ptr, n_int);
	ptr += n_int;

	weights = new Eigen::MatrixXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		weights[i] = Eigen::MatrixXf (input_count, input_count);

		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				memcpy ((void *)&tmp, ptr, n_float);
				ptr += n_float;
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
			memcpy ((void *)&tmp, ptr, n_float);
			ptr += n_float;
			biases[i] (j) = tmp;
		}
	}

	last_weights = new float[input_count];

	for (int i = 0; i < input_count; ++i)
	{
		memcpy ((void *)&tmp, ptr, n_float);
		ptr += n_float;
		last_weights[i] = tmp;
	}
	
	memcpy ((void *)&last_bias, ptr, n_float);
	ptr += n_float;

	delete[] buffer;

	u = Eigen::VectorXf (input_count);
	temp = Eigen::VectorXf (input_count);
	one = Eigen::VectorXf (input_count);
	one.fill (1.0f);
}

int NeuralNet::get_input_count ()
{
	return input_count;
}

int NeuralNet::get_number_of_layers ()
{
	return number_of_layers;
}

Eigen::MatrixXf * NeuralNet::get_weights ()
{
	return weights;
}

Eigen::VectorXf * NeuralNet::get_biases ()
{
	return biases;
}

float * NeuralNet::get_last_weights ()
{
	return last_weights;
}

float NeuralNet::get_last_bias ()
{
	return last_bias;
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

NeuralNet::NeuralNet (NeuralNet & n1, NeuralNet & n2)
{
	input_count = n1.get_input_count ();
	number_of_layers = n1.get_number_of_layers ();

	Eigen::MatrixXf *n1_weights = n1.get_weights ();
	Eigen::MatrixXf *n2_weights = n2.get_weights ();

	weights = new Eigen::MatrixXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		weights[i] = Eigen::MatrixXf (input_count, input_count);

		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				float f;
				int r = rand () % 2;
				r == 1 ? f = n1_weights[i] (j, k) : f = n2_weights[i] (j, k);
				weights[i] (j, k) = f;
			}
		}
	}

	Eigen::VectorXf *n1_biases = n1.get_biases ();
	Eigen::VectorXf *n2_biases = n2.get_biases ();

	biases = new Eigen::VectorXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		biases[i] = Eigen::VectorXf (input_count);

		for (int j = 0; j < input_count; ++j)
		{
			float f;
			int r = rand () % 2;
			r == 1 ? f = n1_biases[i] (j) : f = n2_biases[i] (j);
			biases[i] (j) = f;
		}
	}

	float *n1_last_weights = n1.get_last_weights ();
	float *n2_last_weights = n2.get_last_weights ();

	last_weights = new float[input_count];

	for (int i = 0; i < input_count; ++i)
	{
		float f;
		int r = rand () % 2;
		r == 1 ? f = n1_last_weights[i] : f = n2_last_weights[i];
		last_weights[i] = f;
	}

	float f;
	int r = rand () % 2;
	r == 1 ? f = n1.get_last_bias () : f = n2.get_last_bias ();
	last_bias = f;
}

NeuralNet::~NeuralNet ()
{
	delete[] weights;
	delete[] biases;
	delete[] last_weights;
}
