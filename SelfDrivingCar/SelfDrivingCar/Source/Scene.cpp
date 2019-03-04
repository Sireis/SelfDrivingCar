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
		float color1[] = { 1.0f, 0.5f, 0.0f, 0.5f };
		float color2[] = { 1.0f, 0.0f, 0.0f, 0.5f };
		rec = new Drawing::Rectangle (0.0f, 0.0f, 0.1f, 0.4f, color1);
		rec2 = new Drawing::Rectangle (0.0f, 0.0f, 0.1f, 0.4f, color2);
		rec->rotate (3.1415926535f);
	}
	/*
	T += dt;
	rec->rotate (T * 2 * 3.1415926535f );*/
	rec->translate (0,dt);
	rec2->translate (dt, 0);
}
