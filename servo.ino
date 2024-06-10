#include <Servo.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Servo servo;
  servo.attach(3); //3번포트쪽으로 제어신호 들어가게(?)
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);
  int nAng = servo.read();
  Serial.println(nAng);
}
