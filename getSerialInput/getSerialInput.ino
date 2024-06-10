#include <StringTok.h>
#define NUM_CHECK_LINE (5)

String getSerialInput()
{
  StringTok stInput;
  scans(stInput); //wait and return string
  if (!stInput.isEmpty())
  {
    int nCheckLine=0;
    while (!stInput.hasLine()) //true: enter o, false: enter x
    {
      stInput.appendSerial(); //appendSerial() -> serial로부터 입력받아 StringTok에 붙이기 
      nCheckLine++;
      if(nCheckLine > NUM_CHECK_LINE)
      {
        break;
      }
    }         
  }  
  return stInput.toString();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String str = getSerialInput();
  Serial.println("input = "+ str);
  
}
