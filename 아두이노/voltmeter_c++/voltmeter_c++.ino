#include <voltmeter.h>
#define SERIAL_BPS (9600)
#define DELAY_MS (1000)
Voltmeter voltmeter(A2); //instance 생성 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  double volt = voltmeter.getVolt();
  Serial.println("v = "+ String(volt));
  delay(DELAY_MS);
}
