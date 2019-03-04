#pragma once
class MatrixMath
{
public:
	static void multiply_m4x4_m4x4 (const float *left, const float *right, float *result);
	static void multiply_m4x4_v4 (const float *left, const float *right, float *result);

private:
	MatrixMath ();
	~MatrixMath ();
};

