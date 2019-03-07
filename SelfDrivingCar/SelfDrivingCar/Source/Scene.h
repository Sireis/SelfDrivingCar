#pragma once

#include "Updateable.h"
#include "Car.h"


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
};

