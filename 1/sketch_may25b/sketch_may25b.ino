#define PIN_LED_BLUE (2)
#define PIN_LED_RED (3)
#define PIN_LED_GREEN (4)
#define PIN_BTN_LEFT (5)
#define PIN_BTN_RIGHT (6)
#define PIN_TRIG (8)
#define PIN_ECHO (9)
#define PIN_BUZZ (10)
#define PORT_RAND (A1)
#define SERIAL_RATE (9600)
#define SERIAL_DEALY (50)
#define PULSE_WIDTH (30) // in usec
#define PULSE_TIMEOUT (50000) // in usec
#define MIN_RANGE (50.) //in mm


//////////////
//초기화///////
//////////////

void init3Led() {
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  stop3Led();
}

void initRand() {
  int nVolt = analogRead(PORT_RAND);
  randomSeed(nVolt); // 난수를 초기화
}

void initbutton() {
  pinMode(PIN_BTN_LEFT, INPUT_PULLUP);
  pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);
}

void initBuzz() {
  pinMode(PIN_BUZZ, OUTPUT);
}

void initEcho() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void initGame() {
  init3Led();
  initRand();
  initbutton();
  initBuzz();
  initEcho();
  Serial.begin(SERIAL_RATE);
}

//////////////////
////LED METHOD////
//////////////////

void startLed(int nPin) {
  digitalWrite(nPin, HIGH);
}

void stopLed(int nPin) {
  digitalWrite(nPin, LOW);
}

void stop3Led() {
  digitalWrite(PIN_LED_BLUE, LOW);
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}

int getRandLedPin() {
  int nRand = random(3); //0 1 2 가 나옴
  return nRand + PIN_LED_BLUE; // 0 1 2 --> 2 3 4
}


//////////////////
////BTN METHOD////
//////////////////
bool checkLeftButton()  //누르면 True, 평소는 False
{
  int nInput= digitalRead(PIN_BTN_LEFT); //평소 HIGH 누르면 LOW
  return nInput==LOW;
}

bool checkRightButton()  //누르면 True, 평소는 False
{
  int nInput= digitalRead(PIN_BTN_RIGHT); //평소 HIGH 누르면 LOW
  return nInput==LOW;
}


long checkButtonEcho(bool& bLeftInput, bool& bRightInput, bool& bCenterInput) {
  long  nStartTime = millis();
  bLeftInput = bRightInput = bCenterInput=false;
  while (1) {
    bLeftInput = checkLeftButton(); //평소 HIGH 누르면 LOW
    bRightInput = checkRightButton();
    bCenterInput = checkEcho();
    if (bLeftInput || bRightInput || bCenterInput) break;
  }
  long  nStopTime = millis();
  return nStopTime - nStartTime;
}

int evalInput(int nLed, bool bLeftInput, bool bRightInput, bool bCenterInput)
{
  if(nLed==PIN_LED_RED)
  {
    if (bLeftInput == true && bRightInput == false && bCenterInput==false) return 1;
    else return 0;
  }
  else if (nLed == PIN_LED_BLUE)
  {
    if(bLeftInput == false && bRightInput == true && bCenterInput==false) return 1;
    else return 0;
  }
  else // nLed == PIN_LED_GREEN
  {
    if(bLeftInput == false && bRightInput == false && bCenterInput==true) return 1;
    else return 0;
  }
}
/////////////////////
////MELODY METHOD////
/////////////////////

void playMelody() {
  tone(PIN_BUZZ, 1000);
  delay(500);
  tone(PIN_BUZZ, 500);
  delay(500);
  tone(PIN_BUZZ, 400);
  delay(500);
}

void stopMelody() {
  noTone(PIN_BUZZ);
}

//////////////////
///Echo METHOD////
//////////////////

void makeTrigger() {
  //trigger
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(PULSE_WIDTH); // in usec
  digitalWrite(PIN_TRIG, LOW);
}

//in mm
double getEchoRange() {
  long nEchoTime = pulseIn(PIN_ECHO, HIGH, PULSE_TIMEOUT);
  double range = nEchoTime * 1e-6 * 340./ 1e-3 / 2.; // in mm; 음속 : 340 m/s, 1e-6 - 1usec, 1e-3 - 1mm
  return range;
}

bool checkEcho()
{
  makeTrigger();
  double range=getEchoRange();
  bool bResult = range !=0. && range <= MIN_RANGE; // range가 0이면 timeout
  return bResult;
}


void setup() {
  // put your setup code here, to run once:
  initGame();
  playMelody();
  stopMelody();
}

void loop() {
  // put your main code here, to run repeatedly:
  int nRandLed = getRandLedPin();
  bool bLeftInput, bRightInput, bCenterInput;
  startLed(nRandLed);
  long nTime = checkButtonEcho(bLeftInput, bRightInput, bCenterInput);
  int nScore=evalInput(nRandLed,bLeftInput, bRightInput, bCenterInput);
  stopLed(nRandLed);
  delay(1000);
  Serial.println("left = " + String(bLeftInput) + " |right = " + String(bRightInput)+"|center = "+String(bCenterInput));
  Serial.println("Time = " + String(nTime * 1e-3) + "sec");
  Serial.println("score = " + String(nScore));
}
