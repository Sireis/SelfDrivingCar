#include "stdafx.h"
#include "Listed.h"
#include "ListProcessor.h"


Listed::Listed ()
{
	ListProcessor::add (this);
}


Listed::~Listed ()
{
}

void Listed::update1 (const double &dt)
{
}

void Listed::update2 ()
{
}

bool Listed::to_be_disposed ()
{
	return dispose_on_next_update;
}

void Listed::dispose ()
{
	dispose_on_next_update = true;
}

void Listed::tag (int t)
{
	this->t = t;
}
