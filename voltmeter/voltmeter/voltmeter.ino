// 전압계 구성
#define SERIAL_BPS  (9600)
#define DELAY_MS    (1000)
int nVoltPort = A2;

int getStep(){
  return analogRead(nVoltPort);
}

double getVolt(){
  int nStep = getStep();  
  return nStep*5/(double)1023;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  double volt = getVolt();
  Serial.println("v = " + String(volt));
  delay(DELAY_MS);
}
