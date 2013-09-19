#include <PPM.h>

int pin = 10;

void setup() {
  Serial.begin(9600);
  setPPMLength(22500); // in microseconds (20000 us - default)
  ppmMode(pin, INPUT);  
}

void loop() {
  long signal = ppmRead(pin);
  Serial.println(signal);
  delay(500);
}
