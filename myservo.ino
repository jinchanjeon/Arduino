#include <MyServo.h>

MyServo servo;

void setup() {
  // put your setup code here, to run once:
  servo.setPort(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.move(0);
  servo.move(180);
  
}
