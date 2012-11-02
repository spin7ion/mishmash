/*
 * Euler.cpp
 *
 *  Created on: 16.10.2012
 *      Author: pankratov
 */

#include "Euler.h"

Euler::Euler(float yaw, float pitch, float roll, float unit) {
	set(yaw, pitch, roll, unit);
}

void Euler::set(float yaw, float pitch, float roll, float unit) {
	angles[YAW] = yaw*unit;
	angles[PITCH] = pitch*unit;
	angles[ROLL] = roll*unit;
}

void Euler::set(float value, int angle, float unit) {
	angles[angle] = value*unit;
}

float Euler::get(int angle, float unit) {
	return angles[angle]/unit;
}

const Euler operator +(const Euler& left, const Euler& right) {
	return Euler(left.angles[0] + right.angles[0],
			left.angles[1] + right.angles[1],
			left.angles[2] + right.angles[2]);
}

const Euler operator -(const Euler& left, const Euler& right) {
	return Euler(left.angles[0] - right.angles[0],
			left.angles[1] - right.angles[1],
			left.angles[2] - right.angles[2]);
}

const Euler operator -(const Euler& value) {
	return Euler(-value.angles[0],
			-value.angles[1],
			-value.angles[2]);
}

const Euler operator *(float left, const Euler& right) {
	return Euler(left*right.angles[0],
			left*right.angles[1],
			left*right.angles[2]);
}

const Euler operator /(const Euler& left, float right) {
	return Euler(left.angles[0] / right,
			left.angles[1] / right,
			left.angles[2] / right);
}

Euler::~Euler() {
	// TODO Auto-generated destructor stub
}

