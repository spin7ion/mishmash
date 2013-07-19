#include "Arduino.h"
#include <MotorDriver.h>

#define LEFT_FORWARD_MOTOR 		9
#define LEFT_BACKWARD_MOTOR		10
#define RIGHT_FORWARD_MOTOR 	6
#define RIGHT_BACKWARD_MOTOR 	3

#define TIME_DELAY 	10
MotorDriver::MotorDriver(int forwardPin,int backwardPin,bool inverseSpeed)
{
	speedInPercent=0;
	speed=0;
	mode=STOP;
	maxSpeed=255;
	minSpeed=0;
	last_time=0;
	this->forwardPin=forwardPin;
	this->backwardPin=backwardPin;
	this->inverseSpeed=inverseSpeed;
	setMode(STOP);
}
void MotorDriver::setPins(int forwardPin,int backwardPin){
	this->forwardPin=forwardPin;
	this->backwardPin=backwardPin;
}
void MotorDriver::setSpeedPercent(int speedInPercent,bool wait)
{ 
	if(speed>100)
		speed=100;
	if(speed<0)
		speed=0;	
	this->speedInPercent=speedInPercent;
	new_speed=minSpeed+this->speedInPercent*(maxSpeed-minSpeed)/100;
	if(wait)
		waitRenew();
}
int MotorDriver::getSpeedPercent()
{ 
	return speedInPercent;
}
void MotorDriver::setSpeedConvert(int minSpeed,int maxSpeed)
{
	if(minSpeed>=maxSpeed) //bad params, exit
		return;
	if(minSpeed<0)
		minSpeed=0;
	if(maxSpeed>255)
		maxSpeed=255;
	this->minSpeed=minSpeed;
	this->maxSpeed=maxSpeed;
}
void MotorDriver::setSpeedPWM(int speed,bool wait){
	if(speed>255)
		speed=255;
	if(speed<0)
		speed=0;		
	new_speed=speed;
	if(wait)
		waitRenew();
}
int MotorDriver::getSpeedPWM(){	
	return speed;
}
void MotorDriver::setMode(int mode,bool wait)
{
	new_mode=mode;
	if(wait)
		waitRenew();
}
int MotorDriver::getMode()
{ 
	return mode;
}
void MotorDriver::setModeSpeedPWM(int mode,int speed,bool wait)
{
	setMode(mode,false);
	setSpeedPWM(speed,false);
	if(wait)
		waitRenew();
}
void MotorDriver::setModeSpeedPercent(int mode,int speed,bool wait)
{
	setMode(mode,false);
	setSpeedPercent(speed,false);
	if(wait)
		waitRenew();
}
void MotorDriver::waitRenew()
{
	while(renewConf()){			
		delay(TIME_DELAY);
	}
}

void MotorDriver::stop()//all Motors off, not set Mode or Speed
{
	analogWrite(backwardPin, 0);
	analogWrite(forwardPin, 0);   
 
}

void MotorDriver::moveForward()
{
	if(inverseSpeed)
	{
		analogWrite(backwardPin, 255);
		analogWrite(forwardPin, 255-speed);   
	}
	else
	{
		analogWrite(backwardPin, 0);
		analogWrite(forwardPin, speed);   
	}
}
void MotorDriver::moveBackward()
{
	if(inverseSpeed)
	{
		analogWrite(forwardPin, 255);
		analogWrite(backwardPin, 255-speed);   
	}
	else
	{
		analogWrite(forwardPin, 0);
		analogWrite(backwardPin, speed);   
	}
}	
	
bool MotorDriver::renewConf()
{
//	if(millis()->=TIME_DELAY)
	{
		last_time=millis();
		if(mode!=new_mode){
			if(speed>0)
				speed--;
			else
				mode=new_mode;
		}
		if((mode==new_mode)&&(mode!=STOP))
		{
			if(speed>new_speed)
				speed--;
			if(speed<new_speed)
				speed++;
		}
		speedInPercent=(speed-minSpeed)*100/(maxSpeed-minSpeed);
		switch(this->mode){
			case STOP:
				stop();
				break;
			case MOVE_FORWARD:
				moveForward();
				break;
			case MOVE_BACKWARD:
				moveBackward();
				break;				
			default://bad params, stop
				this->mode=STOP;
				stop();
		}
	}
	if(mode==STOP)
		return (mode!=new_mode);	
	else	
		return ((speed!=new_speed)||(mode!=new_mode));
}
