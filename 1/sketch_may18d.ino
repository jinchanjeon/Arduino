void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //pinMode(5, INPUT);  //HIGH(5V, 위험) or LOW(0V)
  //pinMode(6, INPUT);
  pinMode(5, INPUT_PULLUP); // 평상시 HIGH(Arduino 내부 전압 사용해서 안전), 누르면 LOW(0V)
  pinMode(6, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int nLeftInput=digitalRead(5); // 평소 HIGH, 누르면 LOW
  int nRightInput = digitalRead(6);
  Serial.println("left= " + String(nLeftInput) + "|right= " +String(nRightInput));
  if (nLeftInput==LOW) Serial.println("Left button is pressed");
  if (nRightInput==LOW) Serial.println("Right button is pressed");
  delay(200);
}
