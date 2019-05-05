#pragma once
#include "Updateable.h"
#include "NeuralNet.h"
#include "Rectangle.h"
#include "Circle.h"

class NeuralVisualization :	public Updateable
{
public:
	NeuralVisualization (Vec2 position, NeuralNet *net);
	~NeuralVisualization ();

	void update (const double &dt) override;

private:
	NeuralNet *net;

	Drawing::Rectangle *anchor;
	Drawing::Circle **inputs;
	Drawing::Circle **biases;
	Drawing::Circle *last_bias;
	Drawing::Rectangle **weights;
	Drawing::Rectangle **last_weights;
};

