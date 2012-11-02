/*
 * Quaternion.h
 *
 * Description: quaternion math
 * Email: vasiliy@mishinmachines.com
 * Site: http://www.mishinmachines.com
 *
 *  Created on: 16.10.2012
 *      Author: pankratov.vs
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <math.h>

#define X 1
#define Y 2
#define Z 3

class Quaternion {
public:
	float elem[4];

	Quaternion(float e0=0.0, float e1=0.0, float e2=0.0, float e3=0.0);
	void set(float e0, float e1, float e2, float e3);

	const Quaternion conjugate();
	float absolute();
	const Quaternion normalize();

	friend const Quaternion operator*(const Quaternion& left,
					const Quaternion& right);
	friend const Quaternion operator*(float left,
						const Quaternion& right);
	friend const Quaternion operator/(const Quaternion& left,
						float right);
	friend const Quaternion operator+(const Quaternion& left,
						const Quaternion& right);
	friend const Quaternion operator-(const Quaternion& left,
						const Quaternion& right);
	friend const Quaternion operator-(const Quaternion& value);
	float operator[](int index);

	virtual ~Quaternion();
};

#endif /* QUATERNION_H_ */
