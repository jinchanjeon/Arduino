#define PIN_TRIG (8)
#define PIN_ECHO (9)
#define PULSE_WIDTH (30) // in usec
#define PULSE_TIMEOUT (50000) // in usec

void initEcho() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void makeTrigger() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(PULSE_WIDTH); // in usec
  digitalWrite(PIN_TRIG, LOW);
}

double getEchoRange(){
   long nEchoTime = pulseIn(PIN_ECHO, HIGH, PULSE_TIMEOUT);
  double range = nEchoTime * 1e-6 * 340 / 1e-3 / 2.; // in mm; 음속 : 340 m/s, 1e-6 - 1usec, 1e-3 - 1mm
  return range;
}

void setup() {
  // put your setup code here, to run once:
  initEcho();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  makeTrigger();
  // echo 받기
  double range = getEchoRange();
  Serial.println("range = "+String(range)+"mm");
  delay(1000);

}
