#include "Arduino.h"
#include <MiniQDriver.h>
#include <MotorDriver.h>
#define LEFT_FORWARD_MOTOR 		9
#define LEFT_BACKWARD_MOTOR		10
#define RIGHT_FORWARD_MOTOR 	6
#define RIGHT_BACKWARD_MOTOR 	3

#define TIME_DELAY 	10
MiniQDriver::MiniQDriver()
{
	motor1= new MotorDriver(6,3);
	motor2= new MotorDriver(9,10,true);
}
MiniQDriver::MiniQDriver(int leftForwardMotor,int leftBackwardMotor,int rightForwardMotor,int rightBackwardMotor)
{
	motor1= new MotorDriver(rightForwardMotor,rightBackwardMotor);
	motor2= new MotorDriver(leftForwardMotor,leftBackwardMotor,true);
	setMode(STOP);
}
void MiniQDriver::setPins(int leftForwardMotor,int leftBackwardMotor,int rightForwardMotor,int rightBackwardMotor){
	motor1->setPins(rightForwardMotor,rightBackwardMotor);
	motor2->setPins(leftForwardMotor,leftBackwardMotor);
}
void MiniQDriver::setSpeedPercent(int speedInPercent,bool wait)
{ 
	motor1->setSpeedPercent(speedInPercent,false);
	motor2->setSpeedPercent(speedInPercent,false);
	if(wait)
		waitRenew();
}
int MiniQDriver::getSpeedPercent()
{ 
	return motor1->getSpeedPercent();
}
void MiniQDriver::setSpeedConvert(int minSpeed,int maxSpeed)
{
	motor1->setSpeedConvert(minSpeed,maxSpeed);
	motor2->setSpeedConvert(minSpeed,maxSpeed);
}
void MiniQDriver::setSpeedPWM(int speed,bool wait){
	motor1->setSpeedPWM(speed,false);
	motor2->setSpeedPWM(speed,false);
	if(wait)
		waitRenew();
}
int MiniQDriver::getSpeedPWM(){	
	return motor1->getSpeedPWM();
}
void MiniQDriver::setMode(int mode,bool wait)
{
	switch(mode){
		case TURN_LEFT:
			motor1->setMode(MOVE_FORWARD,false);
			motor2->setMode(MOVE_BACKWARD,false);
			break;
		case TURN_RIGHT:
			motor1->setMode(MOVE_BACKWARD,false);
			motor2->setMode(MOVE_FORWARD,false);
			break;					
		default:
			motor1->setMode(mode,false);
			motor2->setMode(mode,false);
		}
	if(wait)
		waitRenew();
}
int MiniQDriver::getMode()
{ 
	return motor1->getMode();
}
void MiniQDriver::setModeSpeedPWM(int mode,int speed,bool wait)
{
	setMode(mode,false);
	setSpeedPWM(speed,false);
	if(wait)
		waitRenew();
}
void MiniQDriver::setModeSpeedPercent(int mode,int speed,bool wait)
{
	setMode(mode,false);
	setSpeedPercent(speed,false);
	if(wait)
		waitRenew();
}
void MiniQDriver::waitRenew()
{
	while(renewConf()){			
		delay(TIME_DELAY);
	}
}
bool MiniQDriver::renewConf()
{
	bool b1=motor1->renewConf();
	bool b2=motor2->renewConf();
	return (b1)||(b2);

}
