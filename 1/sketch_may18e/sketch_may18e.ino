#define PIN_LED_BLUE (2)
#define PIN_LED_RED (3)
#define PIN_LED_GREEN (4)
#define PIN_BTN_LEFT (5)
#define PIN_BTN_RIGHT (6)
#define SERIAL_RATE (9600)
#define SERIAL_DELAY (50)
#define PORT_RAND (A1)

///////
//초기화
//////
void init3Led()
{
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  stop3Led();
}

void initRand()
{
  int nVolt = analogRead(PORT_RAND);
  randomSeed(nVolt); //난수 초기화
}

void initButton()
{
  pinMode(PIN_BTN_LEFT, INPUT_PULLUP);
  pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);
}

void initGame()
{
  init3Led();
  initRand();
  initButton();
  Serial.begin(SERIAL_RATE);
}

/////////
// LED Method
////////

void startLed(int nPin)
{
  digitalWrite(nPin,HIGH);
}

void stopLed(int nPin)
{
  digitalWrite(nPin,LOW);
}

void stop3Led()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}


int getRandLedPin()
{
  int nRand = random(3);
  return nRand + PIN_LED_BLUE;
}

///////
// 버튼
///////
void checkButton(int& nLeftInput, int& nRightInput)
{
  long nStartTime = millis();
  nLeftInput=nRightInput = HIGH;
  while (1)
  {
    int nLeftInput = digitalRead(PIN_BTN_LEFT);
    int nRightInput = digitalRead(PIN_BTN_RIGHT);
    if(nLeftInput == LOW || nRightInput==LOW) break;
  }
    long nStopTime = millis();
    return nStopTime - nStartTime;
}

void setup() {
  // put your setup code here, to run once:
   initGame();
}

void loop() {
  // put your main code here, to run repeatedly:
 int nRandLed = getRandLedPin();
 startLed(nRandLed);
 delay(SERIAL_DELAY);
 stop3Led();
}
