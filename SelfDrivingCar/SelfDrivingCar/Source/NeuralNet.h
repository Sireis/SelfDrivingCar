#pragma once
class NeuralNet
{
public:
	NeuralNet (const int input_count, const int number_of_layers);
	NeuralNet (std::string path_to_file);
	NeuralNet ();
	~NeuralNet ();

	float output (const float *inputs);
	void save_to_file (std::string);
	void load_from_file (std::string);

private:
	int input_count, number_of_layers;
	float *last_weights;
	float last_bias;

	Eigen::MatrixXf *weights;
	Eigen::VectorXf *biases;
	Eigen::VectorXf u;
	Eigen::VectorXf temp;
	Eigen::VectorXf one;

	Eigen::VectorXf logistic_function (Eigen::VectorXf u);

};

