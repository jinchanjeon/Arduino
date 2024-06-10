#include <StringTok.h>

#define MAX_SENT  (6)
#define MAX_COUNT  (5)
#define SERIAL_BPS  (19200) // bps: bits per second

String sSent = "The Arduino Software\n\
(IDE) allows you\n\
to write programs\n\
and upload them to your board.\n\
In the Arduino Software page\n\
you will find two options:\n";

String arSent[MAX_SENT]; // String array

int nCorrectChar = 0;
int nTotalChar = 0;
double typeSec = 0.;
double correctRatio = 0.;
double cpm = 0.;

void setupSentences(String& sInput) {
  StringTok sent = sInput;
  sInput = "";
  for (int i = 0; i < MAX_SENT; i++) {    
    String str = sent.cutLine();
    str.trim();
    //if (str.length() == 0) break;
    arSent[i] = str;
    Serial.println("[" + String(i) + "] " + arSent[i]); 
  }
}

void initRand() {
  randomSeed(analogRead(0));
}

int getNextSentIndex() {
  return random(0, MAX_SENT);
}

String getNextSent() {
  int nIndex = getNextSentIndex();
  return arSent[nIndex];
}

String getinputAndTime(String& sPrint) {
  unsigned long nStartTime = millis();
  String sInput = input(sPrint);
  unsigned long nEndTime = millis();
  unsigned long nTypeTime = nEndTime - nStartTime;
  typeSec += nTypeTime / 1000.;
  return sInput;
}

// Statistics: nCorrectChar, correctRatio, cpm
void calcCorrectRatio(String& sent, String& sInput) {
  for (int i = 0; i < sent.length(); i++) {
    if (sent[i] == sInput[i]) nCorrectChar++;
  }
  nTotalChar += sent.length();
  correctRatio = nCorrectChar / (double)nTotalChar * 100.;
  cpm = nCorrectChar / typeSec * 60. ; // char per minute: cps*60
}

// Print: nCorrectChar, correctRatio, cpm
void printCorrectRatio() {
  Serial.println("=========================");
  Serial.println("time (sec) = " + String(typeSec, 1) + " sec");
  Serial.println("correct ratio = " + String(correctRatio, 1) + " %");
  Serial.println("cpm + " +  String(cpm));
  Serial.println("=========================");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BPS);
  Serial.println(sSent);
  setupSentences(sSent);
  initRand();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < MAX_COUNT; i++) {
    String sent = getNextSent();
    String sInput = getinputAndTime(sent);
    Serial.println("\n" + sInput);
    calcCorrectRatio(sent, sInput);
  }
  printCorrectRatio();
}
