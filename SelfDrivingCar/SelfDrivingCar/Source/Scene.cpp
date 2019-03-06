#include "stdafx.h"
#include "Scene.h"
#include "Rectangle.h"


Scene::Scene ()
{
}


Scene::~Scene ()
{
}

void Scene::update (const double & dt)
{
	if (n == 0)
	{
		n = 1;
		float color1[] = { 0.0f, 1.0f, 0.0f, 0.5f };
		float color2[] = { 1.0f, 0.0f, 0.0f, 0.5f };
		car = new Car (0.0f, 0.0f, color1);
	}
	
	T += dt;
}
