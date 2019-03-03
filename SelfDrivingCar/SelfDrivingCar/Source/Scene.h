#pragma once

#include "Updateable.h"

class Scene : public Updateable
{
public:
	Scene ();
	~Scene ();

	void update (const double &dt) override;
};

