#pragma once
#include <stdlib.h>
#include <random>

/// <summary>
/// Helper method for Random Float Number Generation in range
/// </summary>
/// <param name="start">the start of the range</param>
/// <param name="end">end of the range</param>
/// <returns>the random generated number</returns>
float RandInRange(float start, float end);


struct Point2Dd
{
	double x = 0;
	double y = 0;

	Point2Dd()
	{
	}

	Point2Dd(double x_tmp, double y_tmp)
	{
		x = x_tmp;
		y = y_tmp;
	}
};

struct Line {
	double slope;
	double intercept;
};