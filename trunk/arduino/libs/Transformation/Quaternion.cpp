/*
 * Quaternion.cpp
 *
 *  Created on: 16.10.2012
 *      Author: pankratov.vs
 */

#include "Quaternion.h"

Quaternion::Quaternion(float e0, float e1, float e2, float e3){
	set(e0, e1, e2, e3);
}

void Quaternion::set(float e0, float e1, float e2, float e3){
	elem[0] = e0;
	elem[1] = e1;
	elem[2] = e2;
	elem[3] = e3;
}

const Quaternion operator *(const Quaternion& left,
		const Quaternion& right) {
	return Quaternion(left.elem[0]*right.elem[0] -
				left.elem[1]*right.elem[1] -
				left.elem[2]*right.elem[2] -
				left.elem[3]*right.elem[3],
					left.elem[0]*right.elem[1] +
				left.elem[1]*right.elem[0] +
				left.elem[2]*right.elem[3] -
				left.elem[3]*right.elem[2],
					left.elem[0]*right.elem[2] +
				left.elem[2]*right.elem[0] +
				left.elem[3]*right.elem[1] -
				left.elem[1]*right.elem[3],
					left.elem[0]*right.elem[3] +
				left.elem[3]*right.elem[0] +
				left.elem[1]*right.elem[2] -
				left.elem[2]*right.elem[1]
			);
}

const Quaternion operator *(float left,
		const Quaternion& right) {
	return Quaternion(left*right.elem[0],
				left*right.elem[1],
				left*right.elem[2],
				left*right.elem[3]
			);
}

const Quaternion operator/(const Quaternion& left,
						float right) {
	return Quaternion(left.elem[0]/right,
				left.elem[1]/right,
				left.elem[2]/right,
				left.elem[3]/right
			);
}

const Quaternion operator +(const Quaternion& left,
		const Quaternion& right) {
		return Quaternion(left.elem[0]+right.elem[0],
							left.elem[1]+right.elem[1],
							left.elem[2]+right.elem[2],
							left.elem[3]+right.elem[3]);
}

const Quaternion operator -(const Quaternion& left,
		const Quaternion& right) {
		return Quaternion(left.elem[0]-right.elem[0],
							left.elem[1]-right.elem[1],
							left.elem[2]-right.elem[2],
							left.elem[3]-right.elem[3]);
}

const Quaternion operator -(const Quaternion& value) {
		return Quaternion(-value.elem[0],-value.elem[1],
				-value.elem[2],-value.elem[3]);
}

const Quaternion Quaternion::conjugate() {
	return Quaternion(elem[0], -elem[1], -elem[2], -elem[3]);
}

float Quaternion::absolute() {
	return sqrt(elem[0]*elem[0] +
			elem[1]*elem[1] +
			elem[2]*elem[2] +
			elem[3]*elem[3]);
}

const Quaternion Quaternion::normalize() {
	float qabs = absolute();
	return Quaternion(elem[0]/qabs, elem[1]/qabs,
			elem[2]/qabs, elem[3]/qabs);
}

float Quaternion::operator [](int index) {
	return elem[index];
}

Quaternion::~Quaternion() {
	// TODO Auto-generated destructor stub
}

