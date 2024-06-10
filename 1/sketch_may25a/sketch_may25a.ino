#define PIN_BUZZ (10)

void initBuzz()
{
   pinMode(PIN_BUZZ, OUTPUT);
}

void playMelody()
{
  tone(PIN_BUZZ, 1000); //1kHz
  delay(500);
  tone(PIN_BUZZ, 2000); //2kHz
  delay(500);
  tone(PIN_BUZZ, 3000); 
  delay(500);
}

void stopMelody()
{
  noTone(PIN_BUZZ);
}

void setup()
{
  initBuzz();
}

void loop()
{
  playMelody();
  stopMelody();
}
