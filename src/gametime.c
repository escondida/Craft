#include <GLFW/glfw3.h>
#include <math.h>

#include "gametime.h"

float
get_daylight(int daylength)
{
	float timer = time_of_day(daylength);
	if (timer < 0.5) {
		float t = (timer - 0.25) * 100;
		return 1 / (1 + powf(2, -t));
	} else {
		float t = (timer - 0.85) * 100;
		return 1 - 1 / (1 + powf(2, -t));
	}
}

float
time_of_day(int daylength)
{
	if (daylength <= 0) {
		return 0.5;
	}
	float t;
	t = glfwGetTime();
	t = t / daylength;
	t = t - (int)t;
	return t;
}
