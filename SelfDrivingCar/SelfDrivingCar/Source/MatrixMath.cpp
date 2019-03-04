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
	result[0] = left[0] * right[0] + left[1] * right[1]	  + left[2] * right[2] + left[3] * right[3];
	result[1] = left[0] * right[4] + left[1] * right[5]	  + left[2] * right[6] + left[3] * right[7];
	result[2] = left[0] * right[8] + left[1] * right[9]	  + left[2] * right[10] + left[3] * right[11];
	result[3] = left[0] * right[12] + left[1] * right[13] + left[2] * right[14] + left[3] * right[15];
}

MatrixMath::MatrixMath ()
{
}


MatrixMath::~MatrixMath ()
{
}
