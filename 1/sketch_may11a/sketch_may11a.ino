#define SERIAL_RATE (9600)
#define SERIAL_DELAY (50)
#define PORT_RAND (A1)
#define MAX_TYPE_CHAR (26+5)

int nTotalScore=0;  //합산 스코어
int nTotalInputTime =0;  //총 입력 시간(ms)

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
  nTotalScore=0;
}

String getSerialInput()
{
  String str;
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    str+=c;
    delay(SERIAL_DELAY);
  }
  return str;
}

String scanStr()
{
  while (Serial.available() <=0);
  return getSerialInput();
}

int scanInt()
{
  String str = scanStr();
  return str.toInt();
}

void clearSerialInput()
{
  while (Serial.available()>0)
  {
    Serial.read();
    delay(SERIAL_DELAY);
    
  }
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

////////
// Typing Methods
////////
String getUserInput(int& nInputTime)
{ 
  nInputTime=0;
  clearSerialInput();
  int nStartTime = millis();
  String sInput= scanStr();
  int nStopTime=millis();
  nInputTime=nStopTime-nStartTime;
  return sInput;
}

//return score
int compareSentences(String sRand, String sInput)
{// 문장 비교
  int nScore = 0;
  int nRandLen = sRand.length();
  int nInputLen = sInput.length();
  int nMinLen=(nRandLen < nInputLen) ? nRandLen : nInputLen;
  for (int i =0; i<nMinLen; i++)
  {
    if (sRand[i] == sInput[i]) nScore++;
    else nScore--;
  }
  return nScore - abs(nRandLen - nInputLen); 
}

//nTotalScore, nTotalInputTime
void updateStat(int nUserScore, int nInputTime)
{
  //타자 통계
  nTotalScore +=nUserScore;
  nTotalInputTime+=nInputTime;
}

// nTotalScore, nTotalInputTime
void printStat()
{
  //통계 출력
  double typeSpeed = nTotalScore/(double)(nTotalInputTime*1e-3)*60.;
  Serial.println("전체 스코어 = "+String(nTotalScore));
  Serial.println("평균 분당 타자수 = "+String(typeSpeed));
  
}
void setup() {
  // put your setup code here, to run once:
  initGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  String sRand = makeRandSentence(10);
  Serial.println(sRand);
  int nInputTime = 0;
  String sInput = getUserInput(nInputTime);
  Serial.println(sInput);
  Serial.println("입력 시간 = "+ String(nInputTime*1e-3)+"sec");
  int nUserScore = compareSentences(sRand, sInput);
  Serial.println("현재 스코어 = "+String(nUserScore));
  updateStat(nUserScore, nInputTime);
  printStat();
  Serial.println("==========");
}
