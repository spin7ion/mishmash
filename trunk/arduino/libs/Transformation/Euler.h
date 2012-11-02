/*
 * Euler.h
 *
 *  Created on: 16.10.2012
 *      Author: pankratov.vsd
 */

#ifndef EULER_H_
#define EULER_H_

#define YAW 0
#define PITCH 1
#define ROLL 2

#define RAD 1.0
#define DEG 0.0174532925199 // pi/180

class Euler {
private:
	float angles[3];
public:
	Euler(float yaw = 0.0, float pitch = 0.0,
			float roll = 0.0, float unit = RAD);
	void set(float yaw = 0.0, float pitch = 0.0,
			float roll = 0.0, float unit = RAD);
	void set(float value, int angle, float unit = RAD);
	float get(int angle, float unit = RAD);

	friend const Euler operator+(const Euler& left,
						const Euler& right);
	friend const Euler operator-(const Euler& left,
						const Euler& right);
	friend const Euler operator*(float left,
						const Euler& right);
	friend const Euler operator/(const Euler& left,
						float right);
	friend const Euler operator-(const Euler& value);

	virtual ~Euler();
};

#endif /* EULER_H_ */
