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
	bool determine_left ();
	bool determine_right ();
	bool determine_accelerate ();
	bool determine_brake ();
};

