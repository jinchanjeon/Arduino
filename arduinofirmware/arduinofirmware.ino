#include <Servo.h>
#define SERVO_SPEED (180./1500.) //deg/ms
Servo m_servo;

void setPort(int nPort)
{
  if(m_servo.attached()) m_servo.detach();
  m_servo.attach(nPort);

}

void move(int nAng)
{
  int nDelay=int(abs(nAng-getServo())/SERVO_SPEED);
  m_servo.write(nAng);
  delay(nDelay);
}

void swing(int nCount)
{
  move(0);
  for (int i =0; i<nCount;i++)
  {
    move(180);
    move(0);
  }
}

int getServo()
{
  return m_servo.read();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setPort(3);

}

void loop() {
  // put your main code here, to run repeatedly:
  swing(2);
  delay(1000);
}
