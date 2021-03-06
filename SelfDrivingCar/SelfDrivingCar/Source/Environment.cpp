#include "stdafx.h"
#include "Environment.h"
#include "Line.h"


Environment::ShaderInfo Environment::shader;
GLFWwindow *Environment::window;
unsigned long Environment::number_update_cycle = 0;

const float Environment::black[] =	{ 0.0f, 0.0f, 0.0f, 1.0f };
const float Environment::red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
const float Environment::dark_red[] = { 0.59f, 0.0f, 0.0f, 1.0f };
const float Environment::green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
const float Environment::dark_green[] = { 0.0f, 0.59f, 0.0f, 1.0f };
const float Environment::blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
const float Environment::dark_blue[] = { 0.0f, 0.0f, 0.59f, 1.0f };
const float Environment::white[] =	{ 1.0f, 1.0f, 1.0f, 1.0f };
const float Environment::transparent[] = { 0.0f,0.0f,0.0f,0.0f };

float Environment::aspect_ratio = 0.0f;

int Environment::screen_width = 0;
int Environment::screen_height = 0;