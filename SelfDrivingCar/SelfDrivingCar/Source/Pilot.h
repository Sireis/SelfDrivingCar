#pragma once
#include "Updateable.h"
#include "Car.h"
#include "Track.h"

class Pilot : public Updateable
{
public:
	Pilot (Track *track, Car *car);
	Pilot ();
	~Pilot ();

	void update (const double &dt) override;

private:
	Car *car;
	Track *track;

protected:
	float distances[5];

	virtual bool determine_left ();
	virtual bool determine_right ();
	virtual bool determine_accelerate ();
	virtual bool determine_brake ();
};

