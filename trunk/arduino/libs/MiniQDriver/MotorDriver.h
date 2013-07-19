#ifndef MotorDriver_h
#define MotorDriver_h

#include "Arduino.h"

#define STOP       	1
#define MOVE_FORWARD   	2
#define MOVE_BACKWARD  	3

class MotorDriver
{
public:
	MotorDriver(int ForwardPin,int BackwardPin,bool inverseSpeed=false);
	void setPins(int forwardPin,int backwardPin);
	void setSpeedPercent(int speedInPercent,bool wait=true);
	int getSpeedPercent();
	void setSpeedConvert(int minSpeed,int maxSpeed);
	void setSpeedPWM(int speed,bool wait=true);
	int getSpeedPWM();
	void setMode(int mode,bool wait=true);
	int getMode();
	void setModeSpeedPWM(int mode,int speed,bool wait=true);
	void setModeSpeedPercent(int mode,int speed,bool wait=true);
	bool renewConf();
	void waitRenew();
private:
	bool inverseSpeed;
	int minSpeed;
	int maxSpeed;
	int speedInPercent;
	int speed,new_speed;
	int mode,new_mode;//STOP,MOVE_FORWARD,MOVE_BACKWARD
	int last_time;
	int forwardPin;
	int backwardPin;
	void stop();
	void moveForward();
	void moveBackward();	
};
#endif
