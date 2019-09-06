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
	float get_laptime ();
	
	void reset ();

	int index_before = 0;

	void do_drive (bool yes_no);

	typedef void (*lap_finished_callback)(void *obj, int hint, Pilot &pilot, int lap_counter);
	void register_lap_finished (lap_finished_callback ptr, void *obj, int hint);

	typedef void (*crashed_callback)(void *obj, int hint, Pilot &pilot);
	void register_crashed (crashed_callback ptr, void *obj, int hint);

private:
	lap_finished_callback lap_finished_callout;
	crashed_callback crashed_callout;
	void *callee = nullptr;
	int hint = -1;
	double T = 0;
protected:
	Track *track;
	Car *car;
	float distances[6]; //change to union later or rename (currently holds distances AND velocity)

	bool driving = true;
	double lap_time = 9999.0;
	double total_lap_time = 0;

	virtual bool determine_left ();
	virtual bool determine_right ();
	virtual bool determine_accelerate ();
	virtual bool determine_brake ();

	bool going_forward = true;
	int index_now = 0;
	int lap_counter = 0;
};

