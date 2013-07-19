#ifndef MiniQDriver_h
#define MiniQDriver_h

#include "Arduino.h"
#include "MotorDriver.h"

#define TURN_LEFT       4
#define TURN_RIGHT      5

class MiniQDriver
{
public:
	MiniQDriver();
	MiniQDriver(int leftForwardMotor,int leftBackwardMotor,int rightForwardMotor,int rightBackwardMotor);
	void setPins(int leftForwardMotor,int leftBackwardMotor,int rightForwardMotor,int rightBackwardMotor);
	void setSpeedPercent(int speedInPercent,bool wait=true);
	int getSpeedPercent();
	void setSpeedConvert(int minSpeed,int maxSpeed);
	void setSpeedPWM(int speed,bool wait=true);
	int getSpeedPWM();
	void setMode(int mode,bool wait=true);
	int getMode();
	void setModeSpeedPWM(int mode,int speed,bool wait=true);
	void setModeSpeedPercent(int mode,int speed,bool wait=true);
	void pause();
	void resume();
	bool renewConf();
	void waitRenew();
	MotorDriver *motor1,*motor2;
};
#endif
