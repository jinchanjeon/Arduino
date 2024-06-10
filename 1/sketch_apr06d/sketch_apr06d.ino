#define SERIAL_DELAY (50)
int nAlpha;
int nDigit;
int nPunct;
int nSpace;

//serial -> string
String getSerialInput()
{
  String str; //length()==0
  while (Serial.available()>0)
  {
    char c =Serial.read();
    str+=c;
    delay(SERIAL_DELAY);
  }
  return str;
}
void initData()
{
  nAlpha =0;
  nDigit=0;
  nPunct=0;
  nSpace=0;
}

void countString(String str)
{
   for(int i=0; i<str.length();i++)
  {
    char c =str[i];
  if (isAlpha(c)) nAlpha++;
  else if(isDigit(c)) nDigit++;
  else if(isSpace(c)) nSpace++;
  else if(isPunct(c)) nPunct++;
   
  }
}

void printData()
{
  Serial.println("# of alphabet = "+ String(nAlpha));
  Serial.println("# of digit = "+ String(nDigit));
  Serial.println("# of punct = "+ String(nPunct));
  Serial.println("# of space = "+ String(nSpace-1));
  Serial.println("=========");
}

void setup() {
  // put your setup code here, to run once:
  initData();
  Serial.begin(500000);

}

void loop() {
  // put your main code here, to run repeatedly:
  String str= getSerialInput(); 
  if (str.length()>0) 
  {
    Serial.print("Input string: ");
    Serial.println(str);
    countString(str);
    printData();
    initData();
  }
}
