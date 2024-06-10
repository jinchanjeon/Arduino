/*
전압계 만들기
A2 port를 입력으로 하는 전압계 구성 -> serial로 측정 전압 출력
GND(0V), 3.3V, 5V로 확인
*/

#define SERIAL_BPS (9600)
#define DELAY_MS (1000)
int nVoltPort = A2;

int getStep(){
  return analogRead(nVoltPort); //0~1023 리턴
}

double getVolt(){
  int nStep=getStep();
  return nStep*5/(double)1023;

}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  double volt = getVolt();
  Serial.println("v = "+ String(volt));
  delay(DELAY_MS);
}
