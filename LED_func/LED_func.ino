#include <MyLedSensor.h>
#define PIN_LED_R (6)
#define PIN_LED_G (7)
#define PIN_LED_B (5)


void initLed(){
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_R, OUTPUT);
  digitalWrite(PIN_LED_B,LOW);
  digitalWrite(PIN_LED_G,LOW);
  digitalWrite(PIN_LED_R,LOW);  
}

void turnRed(bool bOn){
  digitalWrite(PIN_LED_R, (bOn)? HIGH: LOW);
}

void turnGreen(bool bOn){
  digitalWrite(PIN_LED_G, (bOn)? HIGH: LOW);
}

void turnBlue(bool bOn){
  digitalWrite(PIN_LED_B, (bOn)? HIGH: LOW);
}

// "rgb" "xgb" "rxx", ...
void turnColor(String sColor){
  if (sColor[0]=='r') turnRed(true);
  else if (sColor[0]=='x') turnRed(false);
  if (sColor[1]=='g') turnGreen(true);
  else if (sColor[1]=='x') turnGreen(false);
  if (sColor[2]=='b') turnBlue(true);
  else if (sColor[2]=='x') turnBlue(false);
}

void setup() {
  // put your setup code here, to run once:
  initLed();
}

void loop() {
  // put your main code here, to run repeatedly:
  turnColor("rgb");
  delay(1000);
  turnColor("xxx");
  delay(1000);
  turnColor("rxx");
  delay(1000);
  turnColor("xgx");
  delay(1000);
  turnColor("xxb");
  delay(1000);
  
  /*turnRed(true);
  delay(1000);
  turnRed(false);

  turnGreen(true);
  delay(1000);
  turnGreen(false);

  turnBlue(true);
  delay(1000);
  turnBlue(false);
*/

}
