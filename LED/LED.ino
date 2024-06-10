#define PIN_LED_R (6)
#define PIN_LED_G (7)
#define PIN_LED_B (5)

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_R, OUTPUT);
  digitalWrite(PIN_LED_B,LOW);
  digitalWrite(PIN_LED_G,LOW);
  digitalWrite(PIN_LED_R,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_LED_B,HIGH);
  delay(1000);
  digitalWrite(PIN_LED_B,LOW);

  digitalWrite(PIN_LED_G,HIGH);
  delay(1000);
  digitalWrite(PIN_LED_G,LOW);

  digitalWrite(PIN_LED_R,HIGH);
  delay(1000);
  digitalWrite(PIN_LED_R,LOW);
}
