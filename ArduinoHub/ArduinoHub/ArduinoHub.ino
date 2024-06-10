#include <ArduinoHub.h>
#define SERIAL_BPM (500000)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPM)
}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoHub ardHub;
}
