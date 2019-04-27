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

	void give_new_car (Car* car);
	bool wrong_direction ();
	

	int index_before = 0;

	void do_drive (bool yes_no);

private:
protected:
	Track *track;
	Car *car;
	float distances[5];

	bool driving = true;

	virtual bool determine_left ();
	virtual bool determine_right ();
	virtual bool determine_accelerate ();
	virtual bool determine_brake ();

	bool going_forward = true;
	int index_now = 0;
	int lap_counter = 0;
};

