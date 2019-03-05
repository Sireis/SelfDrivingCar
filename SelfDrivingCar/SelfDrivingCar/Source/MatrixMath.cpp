#include "stdafx.h"
#include "MatrixMath.h"


void MatrixMath::multiply_m4x4_m4x4 (const float * left, const float * right, float * result)
{
	//not done yet
	result[0] = left[0] * right[0] + left[1] * right[2];
	result[1] = left[0] * right[1] + left[1] * right[3];
	result[2] = left[2] * right[0] + left[3] * right[2];
	result[3] = left[2] * right[1] + left[3] * right[3];
}

void MatrixMath::multiply_m4x4_v4 (const float * left, const float * right, float * result)
{
	float temp[4];
	temp[0] = left[0] * right[0] + left[1] * right[1]	 + left[2] * right[2] + left[3] * right[3];
	temp[1] = left[4] * right[0] + left[5] * right[1]	 + left[6] * right[2] + left[7] * right[3];
	temp[2] = left[8] * right[0] + left[9] * right[1]	 + left[10] * right[2] + left[11] * right[3];
	temp[3] = left[12] * right[0] + left[13] * right[1] + left[14] * right[2] + left[15] * right[3];

	result[0] = temp[0]; result[1] = temp[1]; result[2] = temp[2]; result[3] = temp[3];
}

void MatrixMath::multiply_m2x2_v2 (const float * left, const float * right, float * result)
{
	float temp[2];
	temp[0] = left[0] * right[0] + left[1] * right[1];
	temp[1] = left[2] * right[0] + left[3] * right[1];

	result[0] = temp[0]; result[1] = temp[1];
}

MatrixMath::MatrixMath ()
{
}


MatrixMath::~MatrixMath ()
{
}
