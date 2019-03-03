#include "stdafx.h"
#include "Whatever.h"
#include "Source\Drawable.h"
#include "Source\Updateable.h"
#include <iostream>


Whatever::Whatever ()
{
}


Whatever::~Whatever ()
{
}

void Whatever::update (const double & dt)
{
	std::cout << "update(dt=" << dt << ")" << std::endl;
}

void Whatever::draw ()
{
	std::cout << "draw" << std::endl;
}
