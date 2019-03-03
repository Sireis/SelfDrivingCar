#include "Scene.h"
#include <iostream>


Scene::Scene ()
{
}


Scene::~Scene ()
{
}

void Scene::update (const double & dt)
{
	std::cout << "Updating the scene because I can!" << std::endl;
}
