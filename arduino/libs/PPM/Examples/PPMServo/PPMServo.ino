#include <PPM.h>

int pin = 9;

void setup() {
  ppmMode(pin, OUTPUT);  
}

void loop() {
  ppmWrite(pin, 1200);
  delay(2000);
  ppmWrite(pin, 1700);
  delay(2000);
}
