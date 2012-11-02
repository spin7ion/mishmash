#include <Euler.h>
#include <LSM303_T.h>
#include <L3G4200D_T.h>
#include <Transformation.h>
#include <Quaternion.h>

#include <Servo.h>

Transformation trans;
Euler cur;

// Procedure that outputs absolute Euler angles in degrees 
void printAbs(){
	// Gettting absolute Euler angles
	cur = trans.getAbs();
	Serial.print("[ yaw: ");
	Serial.print(cur.get(YAW, DEG));
	Serial.print(", roll: ");
	Serial.print(cur.get(ROLL, DEG));
	Serial.print(", pitch: ");
	Serial.print(cur.get(PITCH, DEG));
	Serial.println("]");
}

// Procedure that outputs relative Euler angles in degrees 
void printFixed(){
	// Gettting relative Euler angles
	cur = trans.getDiff();
	Serial.print("[ yaw: ");
	Serial.print(cur.get(YAW, DEG));
	Serial.print(", roll: ");
	Serial.print(cur.get(ROLL, DEG));
	Serial.print(", pitch: ");
	Serial.print(cur.get(PITCH, DEG));
	Serial.println("]");
}

void setup() {
	Serial.begin(9600);
	Serial.println("Start");
	//Magnetometer callibration 
	//	for calibrating your magnetometer upload following sketch on your Arduino:
	//	[File->Examples->LSM303->Calibrate]
	//	then move your AHRS-board in all possible orientations.
	//	You shold get something like this: 
	//	M  min X: -920 Y: -481 Z: -603 M max X: 357 Y: 805 Z: 590
	//trans.setCalib(minX, maxX, minY, maxY, minZ, maxZ); - enter here your params
	trans.setCalib(-920, 357, -481, 805, -603, 590);
	// initialize AHRS-board	
	trans.init();
}

void loop() {
	// Calculation angles. 
	// It supposed to be executed in every single step off the loop  
	trans.calculate();
	printFixed();
	delay(20);    
}


