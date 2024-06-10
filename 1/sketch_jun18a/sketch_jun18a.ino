#define PIN_LED_BLUE  (2)
#define PIN_LED_RED  (3)
#define PIN_LED_GREEN  (4)
#define PIN_BTN_LEFT  (5)
#define PIN_BTN_RIGHT (6)
#define SERIAL_RATE (9600)
#define SERIAL_DELAY  (50)  // in ms
#define PORT_RAND (A1)
#define PIN_BUZZ  (10)
#define PIN_TRIG  (8)
#define PIN_ECHO  (9)
#define PULSE_WIDTH (30)  //in usec
#define PULSE_TIMEOUT (50000) //in usec
#define MIN_RANGE (50.)   // in mm

int nTotalScore = 0; //총 스코어
long nTotalTime = 0;//총 입력 시간

void start() {
  nTotalScore = 0;
  Serial.println("1. 게임 시작");
  Serial.println("2. 3점 모드");
  Serial.println("3. 게임 종료");
}

void menu() {
  char num = Serial.read();
  if (num == '1') {
    Serial.println("빨간색: 왼쪽 버튼");
    Serial.println("초록색: 초음파 센서");
    Serial.println("파랑색: 오른쪽 버튼");
    while (1) {
      game1();
    }
  }
  else if (num == '2') {
    Serial.println("----------3점 모드---------");
    Serial.println("빨간색: 왼쪽 버튼");
    Serial.println("초록색: 초음파 센서");
    Serial.println("파랑색: 오른쪽 버튼");
    while (1) {
      game2();
    }
  }

  else if (num == '3') {
    Serial.println("게임을 종료합니다.");
    end_melody();
    exit(1);
  }
}

void stopgame() {
  if (nTotalScore < 0) {
    Serial.println("게임을 종료합니다.");
    end_melody();
    start();
    while(1){
      menu();
    }
  }
}

void threescore() {
  if (nTotalScore == 3) {
    Serial.println("게임을 종료합니다. ");
    end_melody();
    start();
    while(1){
      menu();
    }
  }
}

void UpdateStat(int nTime) {
  nTotalTime += nTime;
}



void game1() {
  int nRandLed = getRandLedPin();
  bool bLeftInput, bRightInput, bCenterInput;
  startLed(nRandLed);
  long nTime = checkButtonEcho(bLeftInput, bRightInput, bCenterInput);
  int nScore = evalInput(nRandLed, bLeftInput, bRightInput, bCenterInput);
  UpdateStat(nTime);
  double nSpeed = (double)(nTotalTime * 1e-3) / nTotalScore;
  stopLed(nRandLed);
  delay(1000);
  Serial.println("left = " + String(bLeftInput) + "|right = " + String(bRightInput) + "|center = " + String(bCenterInput));
  Serial.println("반응 시간 = " + String(nTime * 1e-3) + " sec");
  Serial.println("총 스코어 = " + String(nTotalScore));
  Serial.println("평균 반응 시간 = " + String(nSpeed)) + " sec" ;
  Serial.println("================================");
  stopgame();
}

void game2() { // 3점 모드
  int nRandLed = getRandLedPin();
  bool bLeftInput, bRightInput, bCenterInput;
  startLed(nRandLed);
  long nTime = checkButtonEcho(bLeftInput, bRightInput, bCenterInput);
  int nScore = evalInput(nRandLed, bLeftInput, bRightInput, bCenterInput);
  UpdateStat(nTime);
  double nSpeed = (double)(nTotalTime * 1e-3) / nTotalScore;
  stopLed(nRandLed);
  delay(1000);
  Serial.println("left = " + String(bLeftInput) + "|right = " + String(bRightInput) + "|center = " + String(bCenterInput));
  Serial.println("반응 시간 = " + String(nTime * 1e-3) + " sec");
  Serial.println("총 스코어 = " + String(nTotalScore));
  Serial.println("평균 반응 시간 = " + String(nSpeed)) + " sec" ;
  Serial.println("================================");
  stopgame();
  threescore();
}



////////////
///echo 
////////////
void initEcho(){
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
}

void makeTrigger(){
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(PULSE_WIDTH);  // in usec
  digitalWrite(PIN_TRIG, LOW);
}

// in mm
double getEchoRange() {
  long nEchoTime = pulseIn(PIN_ECHO,HIGH,PULSE_TIMEOUT); // in usec
  double range = nEchoTime*1e-6*340./1e-3/2.; // in mm; 음속: 340 m/s, 1e-6 - 1usec,  le-3 = 1mm
  return range;
}

bool checkEcho(){
  makeTrigger();
  double range = getEchoRange();
  bool bResult = range != 0. && range <= MIN_RANGE; // range가 0이면 timeout
  return bResult;
}

////////////
///노래 나오기
////////////
void initBuzz(){
  pinMode(PIN_BUZZ, OUTPUT);
}

void playMelody(){
  tone(PIN_BUZZ, 400);
  delay(10);
}

void wrongMelody()
{
  tone(PIN_BUZZ, 100);
  delay(200);
}

void rightMelody()
{
  tone(PIN_BUZZ,32.7032);
  delay(200);
  tone(PIN_BUZZ,41.2034);
  delay(200);
  tone(PIN_BUZZ,48.9994);
  delay(200);
}

void end_melody() {
  tone(PIN_BUZZ,48.9994);
  delay(200);
  tone(PIN_BUZZ,41.2034);
  delay(200);
  tone(PIN_BUZZ,32.7032);
  delay(200);
  stopMelody();
}

void stopMelody(){
  noTone(PIN_BUZZ);
}

//////////////
// 초기화
//////////////
void init3Led() {
  pinMode (PIN_LED_BLUE, OUTPUT);
  pinMode (PIN_LED_RED, OUTPUT);
  pinMode (PIN_LED_GREEN, OUTPUT);
  stop3Led();
}

void initRand() {
  int nVolt = analogRead(PORT_RAND); // analogRand() @ A0 port: 0(0V) ~ 1023(5V) <-> digitalWrite()
  randomSeed(nVolt);  // 난수 초기화
}

void initButton() {
  pinMode(PIN_BTN_LEFT, INPUT_PULLUP); // 평상시 HIGH(Arduino 내부 전압 사용해서 안전), 누르면 LOW(0V)
  pinMode(PIN_BTN_RIGHT, INPUT_PULLUP);
}

void initGame() {
  init3Led();
  initRand();
  initButton();
  initBuzz();
  initEcho();
  Serial.begin(SERIAL_RATE);
}

//////////////
// LED Method
//////////////
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
  int nRand = random(3);  // 0, 1, 2
  return nRand + PIN_LED_BLUE;  // 0, 1, 2 -> 2, 3, 4
}

////////////////
// Button Method
////////////////
bool checkLeftButton(){ // 누르면 TRUE, 평소는 FALSE
  int nInput = digitalRead(PIN_BTN_LEFT); // 평소 HIGH, 누르면 LOW
  return nInput == LOW;
}

bool checkRightButton(){ // 누르면 TRUE, 평소는 FALSE
  int nInput = digitalRead(PIN_BTN_RIGHT); // 평소 HIGH, 누르면 LOW
  return nInput == LOW;
}

long checkButtonEcho(bool& bLeftInput, bool& bRightInput, bool& bCenterInput) {
  long nStartTime = millis();
  bLeftInput = bRightInput = bCenterInput = false;
  while (1) {
    bLeftInput = checkLeftButton(); // 평소 HIGH, 누르면 LOW
    bRightInput = checkRightButton();
    bCenterInput = checkEcho();
    if (bLeftInput || bRightInput || bCenterInput) break;
  }
  long nStopTime = millis();
  return nStopTime - nStartTime;
}

int evalInput(int nLed, bool bLeftInput, bool bRightInput, bool bCenterInput){
  if (nLed == PIN_LED_RED){
    if(bLeftInput == true && bRightInput == false && bCenterInput == false) 
    { 
      rightMelody();
      nTotalScore++;
    }
    else 
    {
      wrongMelody();
      nTotalScore--;
    }
    
  }
  else if (nLed == PIN_LED_BLUE){
    if(bLeftInput == false && bRightInput == true && bCenterInput == false)
    { 
      rightMelody();
      nTotalScore++;
    }
    else
    {
      wrongMelody();
      nTotalScore--;
    }
  }
  else {
    if(bLeftInput == false && bRightInput == false && bCenterInput == true) 
    {
      rightMelody();
      nTotalScore++;
    }
    else 
    {
      wrongMelody();
      nTotalScore--;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  initGame();
  playMelody();
  stopMelody();
  start();
}

void loop() {
  // put your main code here, to run repeatedly:
  menu();
}
