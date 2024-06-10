#include <StringTok.h>
#define NUM_CHECK_LINE (5)
#define SERIAL_BPS (9600)

/*
  1. 문자열 입력: getSerialInput()
  2. 구문분석: parseCommand()
  3. 연산자별계산: calcWithOp()
  4. 결과 출력: printResult()
*/


//Serial 입력받기
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



//return x,y,op
char parseCommand(double& x, double& y, String sCmd)
{
  StringTok stInput=sCmd;
  StringTok stToken;
  
  stToken = stInput.getToken(); //string "1.2"
  x = stToken.toDouble(); //string->double

  stToken = stInput.getToken(); //string "+"
  char op =  stToken[0];  // +-*/
  
  stToken = stInput.getToken(); //string "3.4"
  y = stToken.toDouble(); //string->double
  return op;
}

double calcWithOp(char op, double x, double y)
{ 
  double ans=0.;

  if (op=='+')
  {
    ans=x+y;
  }
  else if (op == '-')
  {
    ans=x-y;
  }
  else if (op == '*')
  {
    ans=x*y;
  }
  else if (op == '/')
  {
    ans=x/y;
  }
  else if (op == '^')
  {
    ans=pow(x,y);
  }

  return ans;
}

void printResult(double ans)
{
  Serial.println("ans = " + String(ans));
}

void setup() {
    // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  String sCmd = getSerialInput();
  double x,y;
  char op;
  op= parseCommand(x,y,sCmd);
  double ans = calcWithOp(op,x,y);
  printResult(ans);
}
