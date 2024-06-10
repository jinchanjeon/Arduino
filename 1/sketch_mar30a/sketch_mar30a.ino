#define PIN_LED (13)

void initLed(){
  pinMode(PIN_LED , OUTPUT);
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

void doubleblink(){
  onLed(200);
  offLed(100);  
  onLed(200);
  offLed(2500);
}




void blinkJ(){
  blinkZero();
  blinkOne();
  blinkZero();
  blinkZero();
  blinkOne();
  blinkZero();
  blinkOne();
  blinkZero();
  doubleblink();
}

void blinkE(){
  blinkZero();
  blinkOne();
  blinkZero();
  blinkZero();
  blinkZero();
  blinkOne();
  blinkZero();
  blinkOne();
  doubleblink();
}


void blinkO(){
  blinkZero();
  blinkOne();
  blinkZero();
  blinkZero();
  blinkOne();
  blinkOne();
  blinkOne();
  blinkOne();
  doubleblink();
}

void blinkN(){
  blinkZero();
  blinkOne();
  blinkZero();
  blinkZero();
  blinkOne();
  blinkOne();
  blinkOne();
  blinkZero();
  doubleblink();
}

void setup() {
  // put your setup code here, to run once:
  initLed();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  blinkJ();
  blinkE();
  blinkO();
  blinkN();

}
