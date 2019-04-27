#pragma once

#include "Listed.h"
#include "Updateable.h"

class Drawable : virtual public Updateable, virtual public Listed
{
public:
	Drawable (const unsigned int number_of_points, const Vec2 m, const Vec2 direction);
	virtual ~Drawable ();

	virtual void draw () = 0;

	void rotate (const float rad);
	void translate (const float dx, const float dy);
	void set_position (const Vec2 &position);
	void set_parent (Drawable *parent);
	void get_middle (float *middle_x_y);
	void get_rotation (float *rotation_matrix);
	void set_level (const char level);
	int get_level ();
	void visible (bool visibility);
		
private:
	bool first_iteration = true;
	bool is_visible = true;
	void setup ();
	void update (const double &dt) override;
	void update2 () override;
	
protected:
	GLuint VBO;
	Drawable *parent = nullptr;
	float *vertices = nullptr;
	float *original_vertices = nullptr;
	float *model_vertices = nullptr;
	float model_offset[2] = { 0.0f, 0.0f };
	const unsigned int number_of_points;

	float m[2], original_m[2], model_m[2];
	float direction[2], original_direction[2], model_direction[2];

	float rotation[4] = {1.0f, 0.0f, 0.0f, 1.0f};

};

