#define PIN_LED (13)

void initLed(){
  pinMode(PIN_LED, OUPUT);  
}
void onLed(int nDelay){
  digitalWrite(PIN_LED, HIGH);
  delay(nDelay);
}

void offLed(int nDelay){
  digitalWrite(PIN_LED, LOW);
  delay(nDelay);
}

void blinkZero(){
 onLed(500);
 offLed(2500);
}
void blinkOne(){
  onLed(2000);
  offLed(1000);
}

void doubleBlink(){
    onLed(200);
    offLed(100);
    onLed(200);
    offLed(2500);
}
 
void setup() {
  // put your setup code here, to run once:
  initLed();
}

1001010  1000101  1001111  1001110

void loop() {
  // put your main code here, to run repeatedly:
  doubleBlink();
  blinkZero();
  blinkOne();


}
