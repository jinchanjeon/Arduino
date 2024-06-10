#define SERIAL_DELAY (50)
#define SERIAL_RATE (9600)

int PIN_LED=13;
int nPeriod = 3000;
int nEndBlink = 2;

//=======
//String methods
//=======
//Serial -> String
String getSerialInput()
{
  String str;
  while (Serial.available() >0)
  {
    char c = Serial.read();
    str+=c;
    delay(SERIAL_DELAY);
  }
  return str;
}

//scanf : Serial -> String
String scanfStr()
{
  while (Serial.available() <= 0);
  return getSerialInput();
}

//scanf : Serial -> String -> int
int scanInt()
{
  String str = scanfStr();
  return str.toInt();
}

void clearSerialInput()
{
  while (Serial.available() >0)
  {
    Serial.read();
    delay(SERIAL_DELAY);
  }
}

String toBinStr(char c)
{
  String sBin = String((int) c, BIN);
  return sBin;
}

int inputInt(String sInfo)
{
  Serial.print(sInfo);
  int nResult = scanInt();
  Serial.println(nResult);
  return nResult;
}

//=======
//Blink methods
//=======
//scanfInt()
void setLedStates()
{
  // Pin number for LED
  PIN_LED = inputInt("Pin #: ");
  // Blink period
  nPeriod = inputInt("Blink period (ms): ");
  //manyBlink()
  nEndBlink = inputInt("# of blinks: ");
}

void initLed()
{
  pinMode(PIN_LED,OUTPUT);
}

void onLed(int nDelay)
{
  digitalWrite(PIN_LED,HIGH);
  delay(nDelay);
}

void offLed(int nDelay)
{
  digitalWrite(PIN_LED,LOW);
  delay(nDelay);
}

void blinkZero()
{
  onLed(nPeriod/6);
  offLed(nPeriod*5/6);
}

void blinkOne()
{
  onLed(nPeriod*2/3);
  offLed(nPeriod/3);
}


void manyBlink()
{
  int nBlinkTime = nPeriod/6;
  int nCount=3*(nEndBlink-1)+2;
  int nOffTime =nBlinkTime/nCount;
  onLed(2*nOffTime);
  for(int i=1;i<nEndBlink;i++)
  {
    offLed(nOffTime);
    onLed(2*nOffTime);
  }
  offLed(nPeriod*5/6);
}

void blinkChar(char c)
{
  String sBin=toBinStr(c);
  Serial.println(String(c)+"="+sBin);
  for(int i =0;i<sBin.length();i++)
  {
    if(sBin[i]=='0')blinkZero();
    if(sBin[i]=='1')blinkOne();
  }
  manyBlink();
}

void blinkStr(String str)
{
  for(int i =0; i<str.length();i++)
  {
    blinkChar(str[i]);    
  }
}

void setup() {
  // put your setup code here, to run once:
  initLed();
  Serial.begin(SERIAL_RATE);
  setLedStates();
}

void loop() {
  // put your main code here, to run repeatedly:
  clearSerialInput();
  String str = scanfStr();
  if(str.length()>0) 
  {                         
    blinkStr(str);
  }
}
