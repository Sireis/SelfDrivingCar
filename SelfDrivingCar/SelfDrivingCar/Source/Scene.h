#pragma once

#include "Updateable.h"
#include "Car.h"
#include "Wall.h"
#include "Track.h"
#include "Pilot.h"
#include "Circle.h"


class Scene : public Updateable
{
public:
	Scene ();
	~Scene ();

	void update (const double &dt) override;
private:
	int n = 0;
	double T = 0.0;
	Car *car;
	//Wall *wall[4];
	Track *track;
	Pilot *pilot;
};

