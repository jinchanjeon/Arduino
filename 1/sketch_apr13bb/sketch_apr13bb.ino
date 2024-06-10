#define SERIAL_DELAY (50)
#define SERIAL_RATE (9600)
#define PIN_LED (13)

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

//=======
//Blink methods
//=======
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
  onLed(500);
  offLed(2500);
}

void blinkOne()
{
  onLed(2000);
  offLed(1000);
}


void doubleblink()
{
  onLed(200);
  offLed(100);
  onLed(200);
  offLed(2500);
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
  doubleblink();
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
}

void loop() {
  // put your main code here, to run repeatedly:
  clearSerialInput();
  String str = getSerialInput();
  if(str.length()>0) 
  {
    Serial.print("Input String: ");
    Serial.println(str);
    blinkStr(str);
  }
}
