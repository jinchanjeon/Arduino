//가장 간단한 계산기
//"1.2+3.4 -> 4.6"


#include <StringTok.h>
#define SERIAL_BPS (9600)
void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  String str="1.2 - 3.4";
  StringTok stInput=str;
  StringTok stToken;
  stToken = stInput.getToken(); //string "1.2"
  Serial.println("token = "+stToken.toString());
  double x = stToken.toDouble(); //string->double

  stToken = stInput.getToken(); //string "+"
  Serial.println("token = "+stToken.toString());
  char op =  stToken[0];  // +-*/

  stToken = stInput.getToken(); //string "3.4"
  Serial.println("token = "+stToken.toString());
  double y = stToken.toDouble(); //string->double

  double ans; //x+y
  if (op=='-') ans=x-y;
  Serial.println("ans = "+ String(ans));
  delay(1000);
}
