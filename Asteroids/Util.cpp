#define _USE_MATH_DEFINES
#include "Util.h"
#include <cmath>

constexpr float TAU = 2 * M_PI;

float Util::turn(float from, float to, float amount) {
	from = normalizeAngle(from);
	to = normalizeAngle(to);

	float delta = to - from;

	if (delta < 0)
		delta += TAU;

	float newAngle;

	if (delta >= M_PI) {
		//Turning clockwise, angle decreasing.
		newAngle = from - amount;
		if (newAngle < 0) {
			newAngle += TAU;
		}
	} else {
		//Turning counter-clockwise, angle increasing.
		newAngle = from + amount;
		if (newAngle >= TAU) {
			newAngle -= TAU;
		}
	}

	float newDelta = to - newAngle;

	if (newDelta < 0)
		newDelta += TAU;

	//Delta changing sign means we passed the target angle
	if ((delta > M_PI) != (newDelta > M_PI)) {
		return to;
	} else {
		return newAngle;
	}
}

float Util::turnDelta(float from, float to, float amount) {
	from = normalizeAngle(from);
	to = normalizeAngle(to);

	float delta = to - from;

	if (delta < 0)
		delta += TAU;

	if (delta < M_PI) {
		//Turning counter-clockwise, angle increasing.
		return std::fminf(delta, amount);
	}
	else {
		//Turning clockwise, angle decreasing.
		return std::fmaxf(delta - TAU, -amount);
	}
}

float Util::angleDifference(float from, float to) {
	from = normalizeAngle(from);
	to = normalizeAngle(to);

	float delta = to - from;

	if (delta < 0)
		delta += TAU;

	if (delta < M_PI) {
		//Turning counter-clockwise, angle increasing.
		return delta;
	}
	else {
		//Turning clockwise, angle decreasing.
		return delta - TAU;
	}
}

//Note, don't use this function for angles outside the range (-2*pi to 4*pi).
float Util::normalizeAngle(float angle) {
	if (angle < 0) {
		return angle + TAU;
	} else if (angle > TAU) {
		return angle - TAU;
	} else {
		return angle;
	}
}