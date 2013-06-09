/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
#define RED    0
#define GREEN  1
#define BLUE   2
#define YELLOW 3
#define VIOLET 4
#define WHITE  5
#define OFF 6


int redPin = 6;
int greenPin = 7;
int bluePin = 5;


void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pwm(0,0,0);
  Serial.begin(9600);
}

void pwm(int red, int green, int blue) {
   analogWrite(redPin, red); 
   analogWrite(greenPin, green);
   analogWrite(bluePin, blue);
}

void color(int col) {
  switch (col) {
          case RED:
            pwm(255,0,0);
          break;
          case GREEN:
            pwm(0,255,0);
          break;
          case BLUE:
            pwm(0,0,255);
          break;
          case YELLOW:
            pwm(80,255,0);
          break;
          case VIOLET:
            pwm(60,0,255);
          break;
          case WHITE:
             pwm(255,255,255);             
          break;       
          case OFF:
             pwm(0,0,0);             
          break;      
  }
  
}

void loop() {
  if (Serial.available()){
      char input = Serial.read();
      switch (input){
          case 1:
            color(BLUE);
          break;
          case 2:
            color(GREEN);
          break;
          case 3:
            color(YELLOW);
          break;
          case 4:
            color(RED);
          break;
          case 5:
            color(VIOLET);
          break;
          case 6:
            color(OFF);
          break;
      }
      delay(50);
  }
}
