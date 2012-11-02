/*
 * Transformation.cpp
 *
 *  Created on: 16.10.2012
 *      Author: pankratov.vs
 */

#include "Transformation.h"

Transformation::Transformation() {
	curOr = Quaternion(1, 0, 0, 0);
	gyro_offset = Quaternion(0, 0, 0, 0);
	accel_offset = Quaternion(0, 0, 0, 0);	

	gyro = Quaternion(0, 0, 0, 0);
	accel = Quaternion(0, 0, 0, 0);
	magnet = Quaternion(0, 0, 0, 0);

	min_x = 0;
	max_x = 0;
	min_y = 0;
	max_y = 0;
	min_z = 0;
	max_z = 0;

	beta = 0.1; // 0.076
	b.set(0, 1, 0, 0);
}

void Transformation::calculate() {
	calculateOrientation();
	calculateTranslation();
}

// magnetometer calibration
void Transformation::setCalib(int minx, int maxx, int miny, int maxy, int minz, int maxz) {
	min_x = minx;
	max_x = maxx;
	min_y = miny;
	max_y = maxy;
	min_z = minz;
	max_z = maxz;	
}

void Transformation::calibrate() {
	// TODO: add writing magnet params to flash
}

float Transformation::getMagnet(int value, int axis) {
	switch(axis){
		case X:
			return (float)(value-min_x)/(max_x-min_x)-0.5;
		case Y:
			return (float)(value-min_y)/(max_y-min_y)-0.5;
		case Z:
			return (float)(value-min_z)/(max_z-min_z)-0.5;
	}
}

void Transformation::calculateOrientation() {
	getData();

	// The Algorythm
	Quaternion gyroQ = gyroQuat();
	Quaternion accmQ = accelMagQuat();

	curOr = curOr + dt*(gyroQ - beta*accmQ);
	curOr.normalize();
}

void Transformation::init() {
	ctime = millis();
	Wire.begin();

	// gyro init
	gyro_dev.writeReg(L3G4200D_CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
	gyro_dev.writeReg(L3G4200D_CTRL_REG4, 0x20); // 2000 dps full scale

	// accelerometer and magnetometer init
	accelMag_dev.writeAccReg(LSM303_CTRL_REG1_A, 0x27); // normal power mode, all axes enabled, 50 Hz
  	accelMag_dev.writeAccReg(LSM303_CTRL_REG4_A, 0x30); // 8 g full scale
	accelMag_dev.init();	
	accelMag_dev.writeMagReg(LSM303_MR_REG_M, 0x00); // continuous conversion mode

	// TODO: read magnet params from flash -> if(min_x = max_x) 

	// calculation of gyro and accelerometer offsets
	Quaternion g_sum(0, 0, 0, 0);
	Quaternion a_sum(0, 0, 0, 0);
	for(int i = 0; i < 50; i++){
		getData();
		g_sum = g_sum + gyro;
		a_sum = a_sum + accel;		
		delay(20);
	}
	gyro_offset = g_sum/50;
	accel_offset = a_sum/50;
	accel_offset.elem[Z] += GRAVITY;
	
	// execute gradient descent for n=500
	getData();
	Quaternion jtf;
	for(int i=0; i<500; i++){
		jtf = accelMagQuat();
		curOr = curOr - beta*jtf;
	}

	// fix current absolute orientation
	fix();

	ctime = millis();
}

void Transformation::getData() {

	gyro_dev.read();
	// gyroscope - angular rate in radian per second
	gyro.set(0, -gyro_dev.g.x, -gyro_dev.g.y, gyro_dev.g.z);
	gyro = GYRO_SCALE*DEG*gyro - gyro_offset;

	accelMag_dev.read();
	// accelerometer
	accel.set(0, accelMag_dev.a.x, accelMag_dev.a.y, -accelMag_dev.a.z);
	accel = accel - accel_offset;

	// magnetometer
	magnet.set(0, getMagnet(accelMag_dev.m.x, X), getMagnet(accelMag_dev.m.y, Y), 
					-getMagnet(accelMag_dev.m.z, Z));

	dt = (millis() - ctime)/1000.0;
	ctime = millis();
}

// translation of quaternion representation to euler-angeles regresentation
Euler Transformation::getAbs() {
	return quat2eu(curOr);
}

Euler Transformation::getDiff() {
	Quaternion diff = fixed.conjugate()*curOr;	
	return quat2eu(diff);
}

void Transformation::fix() {
	fixed = curOr;
}

Euler Transformation::quat2eu(Quaternion q) {
	return Euler(atan2(2*q[1]*q[2] - 2*q[0]*q[3],
			2*q[0]*q[0] + 2*q[1]*q[1] - 1),
				-asin(2*q[1]*q[3] + 2*q[0]*q[2]),
				atan2(2*q[2]*q[3] - 2*q[0]*q[1],
	       2*q[0]*q[0] + 2*q[3]*q[3] - 1));
}

void Transformation::calculateTranslation() {
	// TODO: calculate translation from accelemoter
	//			and current orientarion
}

// orientation from angular rate
Quaternion Transformation::gyroQuat() {
	// quaternion derivative due to the time
	return 0.5*curOr*gyro;
}

// orientation from vector observation
// 		initially assume that there is no magnetic flux,
// 		distortion and linear accelerations (except gravity acceleration)
Quaternion Transformation::accelMagQuat() {
	
	Quaternion res;
	Quaternion a = accel.normalize();
	Quaternion m = magnet.normalize();
	Quaternion q = curOr;

	// gradient of the function of difference between
	// 			sensor data and assumed quaternion
	//			(transposed jacobian [jt] multiplied on the function [f])
	Quaternion jtf;
	// the function
	float f[6];
	f[0] =  2*(q[1]*q[3]-q[0]*q[2])-a[X];
	f[1] = 2*(q[0]*q[1]+q[2]*q[3])-a[Y];
	f[2] = 2*(0.5-q[1]*q[1]-q[2]*q[2])-a[Z];
	f[3] = 2*b[X]*(0.5-q[2]*q[2]-q[3]*q[3])+2*b[Z]*(q[1]*q[3]-q[0]*q[2])-m[X];
	f[4] = 2*b[X]*(q[1]*q[2]-q[0]*q[3])+2*b[Z]*(q[0]*q[1]+q[2]*q[3])-m[Y];
	f[5] = 2*b[X]*(q[0]*q[2]+q[1]*q[3])+2*b[Z]*(0.5-q[1]*q[1]-q[2]*q[2])-m[Z];

	jtf.elem[0] = -2*q[2]*f[0] +
			2*q[1]*f[1] -
			2*b[Z]*q[2]*f[3] +
			(2*b[Z]*q[1]-2*b[X]*q[3])*f[4] +
			2*b[X]*q[2]*f[5];
	jtf.elem[1] = 2*q[3]*f[0] +
			2*q[0]*f[1] -
			4*q[1]*f[2] +
			2*b[Z]*q[3]*f[3] +
			(2*b[X]*q[2]+2*b[Z]*q[0])*f[4] +
			(2*b[X]*q[3]-4*b[Z]*q[1])*f[5];
	jtf.elem[2] = -2*q[0]*f[0]+
			2*q[3]*f[1] -
			4*q[2]*f[2] -
			(4*b[X]*q[2]+2*b[Z]*q[0])*f[3] +
			(2*b[X]*q[1]+2*b[Z]*q[3])*f[4] +
			(2*b[X]*q[0]-4*b[Z]*q[2])*f[5];
	jtf.elem[3] = 2*q[1]*f[0] +
			2*q[2]*f[1] +
			(2*b[Z]*q[1]-4*b[X]*q[3])*f[3] +
			(2*b[Z]*q[2]-2*b[X]*q[0])*f[4] +
			2*b[X]*q[1]*f[5];

	// calculating b
	Quaternion h = q*m*q.conjugate();
	b.set(0, sqrt(h[X]*h[X]+h[Y]*h[Y]), 0, h[Z]);

	//float mu = alpha*dt*gyro.absolute();
	return jtf.normalize();
}
