#include "stdafx.h"
#include "Scene.h"
#include "Rectangle.h"
#include "Car.h"
#include "NeuralTrainer.h"


Scene::Scene ()
{
	track = new Track (Vec2 (-1.00f, -0.30f));

	track->add (Vec2 (-1.00f, -0.20f));			//2
	track->add (Vec2 (-1.00f, -0.10f));
	track->add (Vec2 (-1.00f, -0.00f));
	track->add (Vec2 (-1.05f, +0.10f));			//5
	track->add (Vec2 (-1.15f, +0.20f));
	track->add (Vec2 (-1.26389, +0.319444f));
	track->add (Vec2 (-1.37963, +0.444444f));
	track->add (Vec2 (-1.46065, +0.601852));
	track->add (Vec2 (-1.46991, +0.6875));		//10
	track->add (Vec2 (-1.44676, +0.768519));
	track->add (Vec2 (-1.37037, +0.819444));
	track->add (Vec2 (-1.27315, +0.819444));
	track->add (Vec2 (-1.19676, +0.768519));
	track->add (Vec2 (-1.09722, +0.675926));	//15
	track->add (Vec2 (-0.99537, +0.555556));
	track->add (Vec2 (-0.912037, 0.513889));
	track->add (Vec2 (-0.810185, 0.532407));
	track->add (Vec2 (-0.731481, 0.601852));
	track->add (Vec2 (-0.641204, 0.668981));	//20
	track->add (Vec2 (-0.474537, 0.756944));
	track->add (Vec2 (-0.24537, 0.782407));
	track->add (Vec2 (-0.00462963, 0.782407));
	track->add (Vec2 (0.152778, 0.782407));
	track->add (Vec2 (0.414352, 0.782407));		//25
	track->add (Vec2 (0.69213, 0.782407));
	track->add (Vec2 (0.951389, 0.775463));
	track->add (Vec2 (1.13194, 0.75463));
	track->add (Vec2 (1.28472, 0.696759));
	track->add (Vec2 (1.39583, 0.625));			//30	
	track->add (Vec2 (1.48611, 0.513889));
	track->add (Vec2 (1.54398, 0.381944));
	track->add (Vec2 (1.56019, 0.24537));
	track->add (Vec2 (1.56019, 0.0949074));
	//track->add (Vec2 (1.56019, -0.0671296));	//35
	//track->add (Vec2 (1.56019, -0.217593));
	track->add (Vec2 (1.56019, -0.361111));
	track->add (Vec2 (1.5625, -0.497685));
	track->add (Vec2 (1.52546, -0.664352));
	track->add (Vec2 (1.38426, -0.777778));		//40
	//track->add (Vec2 (1.18519, -0.777778));
	//track->add (Vec2 (1.02083, -0.777778));
	track->add (Vec2 (0.849537, -0.777778));
	track->add (Vec2 (0.708333, -0.706019));
	track->add (Vec2 (0.652778, -0.594907));	//45
	track->add (Vec2 (0.638889, -0.469907));
	//track->add (Vec2 (0.638889, -0.361111));
	//track->add (Vec2 (0.638889, -0.210648));
	track->add (Vec2 (0.638889, -0.0416667));
	track->add (Vec2 (0.664352, 0.0324074));	//50
	track->add (Vec2 (0.712963, 0.12963));
	track->add (Vec2 (0.747685, 0.203704));
	track->add (Vec2 (0.747685, 0.303241));		//--
	track->add (Vec2 (0.685185, 0.391204));
	track->add (Vec2 (0.625, 0.430556));		//55
	track->add (Vec2 (0.548611, 0.451389));
	//track->add (Vec2 (0.497685, 0.451389));
	//track->add (Vec2 (0.418981, 0.451389));
	//track->add (Vec2 (0.333333, 0.451389));
	//track->add (Vec2 (0.238426, 0.451389));		//60
	track->add (Vec2 (0.143519, 0.451389));
	track->add (Vec2 (0.0393519, 0.444444));
	track->add (Vec2 (-0.0625, 0.425926));
	track->add (Vec2 (-0.143519, 0.375));
	track->add (Vec2 (-0.185185, 0.303241));	//65
	track->add (Vec2 (-0.185185, 0.203704));	//--
	track->add (Vec2 (-0.152778, 0.12963));
	track->add (Vec2 (-0.099537, 0.0324074));
	track->add (Vec2 (-0.0486111, -0.0416667));
	//track->add (Vec2 (0.0787037, -0.127315));	//70
	//track->add (Vec2 (-0.048611, -0.210648));
	////track->add (Vec2 (0.108796, -0.273148));
	//track->add (Vec2 (-0.048611, -0.361111));
	track->add (Vec2 (-0.048611, -0.469907));
	track->add (Vec2 (-0.0499999, -0.594907));	//75
	track->add (Vec2 (-0.0972222, -0.706019));
	track->add (Vec2 (-0.231481, -0.777778));
	//track->add (Vec2 (-0.384259, -0.777778));
	//track->add (Vec2 (-0.500000, -0.777778));
	track->add (Vec2 (-0.638889, -0.777778));	//80
	track->add (Vec2 (-0.766204, -0.74537));
	track->add (Vec2 (-0.881944, -0.685185));
	track->add (Vec2 (-0.962963, -0.578704));
	track->add (Vec2 (-0.990741, -0.465278));	
	track->add (Vec2 (-1, -0.372685));			//85
	track->add (Vec2 (-1.00, -0.31));

	Drawing::Circle *circ = new Drawing::Circle (Vec2 (-0.5, 0), 0.03, Environment::blue);
	circ->set_color (0, Environment::green);
	Drawing::Circle *circ1 = new Drawing::Circle (Vec2 (-0.6, 0), 0.02, Environment::blue);
	//Drawing::Circle *circ2 = new Drawing::Circle (Vec2 (-0.7, 0), 0.01, Environment::blue);
	//Drawing::Circle *circ3 = new Drawing::Circle (Vec2 (-0.8, 0), 0.009, Environment::blue);
}

Scene::~Scene ()
{
}

void Scene::update (const double & dt)
{
	static int lmb = 0;
	int left_button_state = glfwGetMouseButton (Environment::window, GLFW_MOUSE_BUTTON_LEFT);
	
	if (n == 0)
	{
		new NeuralTrainer (track);

		car = new Car (-1.0f, -0.3f, Environment::blue);
		//car->set_position (Vec2(0.0,0.0));
		pilot = new Pilot (track, car);
	}

	//float f = track->nearest_point (car->get_position ());
	//std::cout << "Nearest Point: " << f;
	//std::cout << "    Wrong direction: " << pilot->wrong_direction();
	//std::cout << "    Fittness " << f << std::endl;
	   
	if (left_button_state == GLFW_PRESS && lmb == 0)
	{
		double xpos, ypos;
		glfwGetCursorPos (Environment::window, &xpos, &ypos);
		xpos = (xpos - Environment::screen_width /2) / (Environment::screen_width / 2);
		ypos = -(ypos - Environment::screen_height /2) / (Environment::screen_height / 2);
		xpos /= Environment::aspect_ratio;
		track->add (Vec2 ((float) xpos, (float) ypos));
		lmb = 1;
	}

	if (left_button_state == GLFW_RELEASE)
	{
		lmb = 0;
	}
	
	n++;
	T += dt;
}
