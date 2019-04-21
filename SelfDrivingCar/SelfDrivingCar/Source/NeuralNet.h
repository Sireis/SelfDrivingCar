#pragma once
class NeuralNet
{
public:
	NeuralNet (const int input_count, const int number_of_layers);
	NeuralNet (std::string path_to_file);
	NeuralNet (NeuralNet &n1, NeuralNet &n2);
	NeuralNet ();
	~NeuralNet ();

	float output (const float *inputs);
	void save_to_file (std::string);
	void load_from_file (std::string);

	int get_input_count ();
	int get_number_of_layers ();
	Eigen::MatrixXf* get_weights ();
	Eigen::VectorXf* get_biases ();
	float* get_last_weights ();
	float get_last_bias ();

private:
	void init ();

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

