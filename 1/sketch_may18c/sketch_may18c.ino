void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);

  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);

  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

}
