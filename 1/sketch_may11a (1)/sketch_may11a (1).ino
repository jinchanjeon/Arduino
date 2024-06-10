#define SERIAL_RATE (9600)
#define PORT_RAND (A1)
#define MAX_TYPE_CHAR (26+5)

///////////
// Init (타자 초기화)
///////////
void initRand()
{
  int nVolt = analogRead(PORT_RAND);
  randomSeed(nVolt);
}
void initGame()
{
  Serial.begin(SERIAL_RATE);
  initRand();
}

//////////
// Random Sentence (난수 문장)
//////////
char toRandChar(int nRand)
{
  if (nRand <=25) return (char)(nRand+'a');
  else if (nRand ==26) return '.';
  else if (nRand ==27) return ','; 
  else if (nRand ==28) return '?';
  else if (nRand ==29) return '!';
  else if (nRand ==30) return ' ';
  else return ' ';
}

String makeRandSentence(int nRandSize)
{
  String sRand;
  for (int i = 0; i<nRandSize; i++)
  {
    int nRand = random(MAX_TYPE_CHAR);
    char ch = toRandChar(nRand);
    sRand += ch;
  }
  return sRand;
}

void setup() {
  // put your setup code here, to run once:
  initGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("rand = ");
  String sRand = makeRandSentence(10);
  Serial.println(sRand);
  delay(1000);
}
