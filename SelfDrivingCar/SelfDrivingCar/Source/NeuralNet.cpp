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

void NeuralNet::random_step (int factor)
{
	int i, j, k;
	int r = rand () % 4;
	float step = factor * 0.002f;

	switch (r)
	{
		case 0:
			i = rand () % number_of_layers;
			j = rand () % input_count;
			k = rand () % input_count;

			weights[i] (j, k) += step;
			break;
		case 1:
			i = rand () % number_of_layers;
			j = rand () % input_count;

			biases[i] (j) += step;
			break;
		case 2:
			j = rand () % input_count;

			last_weights[j] += step;
			break;
		case 3:
			last_bias += step;
			break;
		default:
			break;
	}

}

void NeuralNet::plot_net () const
{
	std::cout << "Plot of some net" << std::endl;
	std::cout << "weights" << std::endl;

	for (int i = 0; i < number_of_layers; ++i)
	{
		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				std::cout << weights[i] (j, k) << "   ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
	std::cout << "biases" << std::endl;

	for (int i = 0; i < number_of_layers; ++i)
	{
		for (int j = 0; j < input_count; ++j)
		{
			std::cout << biases[i] (j) << "   ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < input_count; ++i)
	{
		std::cout << last_weights[i] << "   "; 
	}

	std::cout << std::endl << std::endl;

	std::cout << last_bias << std::endl;
}

int NeuralNet::get_input_count () const
{
	return input_count;
}

int NeuralNet::get_number_of_layers () const
{
	return number_of_layers;
}

Eigen::MatrixXf * NeuralNet::get_weights () const
{
	return weights;
}

Eigen::VectorXf * NeuralNet::get_biases () const
{
	return biases;
}

float * NeuralNet::get_last_weights () const
{
	return last_weights;
}

float NeuralNet::get_last_bias () const
{
	return last_bias;
}

Eigen::VectorXf NeuralNet::logistic_function (Eigen::VectorXf &u)
{
	u = (-u).array ().exp ();
	return (u + one).cwiseInverse();	
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

NeuralNet::NeuralNet (const NeuralNet & n)
{
	input_count = n.input_count;
	number_of_layers = n.number_of_layers;

	weights = new Eigen::MatrixXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		weights[i] = Eigen::MatrixXf (input_count, input_count);

		for (int j = 0; j < input_count; ++j)
		{
			for (int k = 0; k < input_count; ++k)
			{
				weights[i] (j, k) = n.weights[i](j,k);
			}
		}
	}

	biases = new Eigen::VectorXf[number_of_layers];

	for (int i = 0; i < number_of_layers; ++i)
	{
		biases[i] = Eigen::VectorXf (input_count);

		for (int j = 0; j < input_count; ++j)
		{
			biases[i] (j) = n.biases[i](j);
		}
	}

	last_weights = new float[input_count];

	for (int i = 0; i < input_count; ++i)
	{
		last_weights[i] = n.last_weights[i];
	}

	last_bias = n.last_bias;

	u = Eigen::VectorXf (input_count);
	temp = Eigen::VectorXf (input_count);
	one = Eigen::VectorXf (input_count);
	one.fill (1.0f);
}

NeuralNet & NeuralNet::operator=(const NeuralNet & n)
{
	if (this != &n)
	{
		input_count = n.input_count; number_of_layers = n.number_of_layers;

		weights = new Eigen::MatrixXf[number_of_layers];

		for (int i = 0; i < number_of_layers; ++i)
		{
			weights[i] = Eigen::MatrixXf (input_count, input_count);

			for (int j = 0; j < input_count; ++j)
			{
				for (int k = 0; k < input_count; ++k)
				{
					weights[i] (j, k) = n.weights[i] (j, k);
				}
			}
		}

		biases = new Eigen::VectorXf[number_of_layers];

		for (int i = 0; i < number_of_layers; ++i)
		{
			biases[i] = Eigen::VectorXf (input_count);

			for (int j = 0; j < input_count; ++j)
			{
				biases[i] (j) = n.biases[i] (j);
			}
		}

		last_weights = new float[input_count];

		for (int i = 0; i < input_count; ++i)
		{
			last_weights[i] = n.last_weights[i];
		}

		last_bias = n.last_bias;

		u = Eigen::VectorXf (input_count);
		temp = Eigen::VectorXf (input_count);
		one = Eigen::VectorXf (input_count);
		one.fill (1.0f);
	}

	return *this;
}

NeuralNet::~NeuralNet ()
{
	delete[] weights;
	delete[] biases;
	delete[] last_weights;
}
