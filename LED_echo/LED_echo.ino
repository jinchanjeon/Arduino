#include <MyEchoSensor.h>
#define SERIAL_RATE (9600)
#define DELAY_MS (1000)
#define PIN_TRIG (8)
#define PIN_ECHO (9)
#define PULSE_WIDTH (50)
#define PULSE_TIMEOUT (50000)

void initEcho(){
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void trigger(){
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(PULSE_WIDTH); 
    digitalWrite(PIN_TRIG, LOW);
}

double getEcho(){
  unsigned long nEcho = pulseIn(PIN_ECHO, HIGH, PULSE_TIMEOUT);
  double range = nEcho/2.*1e-6*330./1e-3; //1초동안 소리는 330m 감
  return range;
}

void setup() {
  // put your setup code here, to run once:
  initEcho();
  Serial.begin(SERIAL_RATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  trigger();
  double range=getEcho();
  Serial.println(range);
  delay(200);

}
