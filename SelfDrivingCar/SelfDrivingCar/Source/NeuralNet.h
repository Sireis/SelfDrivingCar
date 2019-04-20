#pragma once
class NeuralNet
{
public:
	NeuralNet (int input_count, int number_of_layers);
	NeuralNet (std::string path_to_file);
	~NeuralNet ();

private:
	float ***weights;
	float *biases;
};

