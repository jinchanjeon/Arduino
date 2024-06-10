#define SERIAL_RATE (9600)
#define SERIAL_DELAY (50)
#define PORT_RAND (A1)
#define MAX_TYPE_CHAR (26+26+5)
#define MAX_TYPE_INT (10)

// 오타 난 부분이랑 개수 알려주기
// 숫자 추가
// 대문자 추가

int nTotalScore = 0; //합산 스코어
int nTotalInputTime = 0; //총 입력 시간(ms)
int nWrong = 0; // 오타개수
int randnum = 10; //숫자

///////////
// Init (타자 초기화)
///////////
void initRand()//난수 초기화
{
  int nVolt = analogRead(PORT_RAND);
  randomSeed(nVolt);
}
void initGame()//타자 초기화
{
  Serial.begin(SERIAL_RATE);
  initRand();
}

//메뉴
void menu()
{
  char n = 0;
  n = Serial.read();
  if (n == 1) return lv1();
  else if (n == 2) return lv2();
  else if (n == 3) return lv3();
  else return error;
}

void error()
{
  Serial.print("1-3만 입력하세요. ");
  return menu();
}


void lv1()
{
  String makeRandSentence(int nRandSize)
  {
    String sRandLv1;

    for (int i = 0; i < nRandSize; i++)
    {
      int nRand = random(MAX_TYPE_CHAR);
      int nRandNum = random(MAX_TYPE_INT);
      char ch = toRandChar(nRand);
      char chc = toRandCharCap(nRand);
      int num = toRandInt(nRandNum);
      sRandLv1 += ch;

    }
    return sRandLv1;
  }
  String sRandLv1 = makeRandSentence(10);
  int nInputTime = 0;

  String sInput = getUserInput(nInputTime);
  Serial.println(sInput);
  Serial.println("입력 시간 = " + String(nInputTime * 1e-3) + "sec");
  int nUserScore = compareSentences(sRand, sInput);
  Serial.println("\n현재 스코어 = " + String(nUserScore));
  updateStat(nUserScore, nInputTime);
  printStat();
  Serial.println("==========");
}

void lv2()
{
  String makeRandSentence(int nRandSize)
  {
    String sRandLv2;

    for (int i = 0; i < nRandSize; i++)
    {
      int nRand = random(MAX_TYPE_CHAR);
      int nRandNum = random(MAX_TYPE_INT);
      char ch = toRandChar(nRand);
      char chc = toRandCharCap(nRand);
      int num = toRandInt(nRandNum);
      sRandLv2 = sRandLv1 + chc;
    }
    return sRandLv2;
  }

  String sRandLv2 = makeRandSentence(10);
  int nInputTime = 0;

  String sInput = getUserInput(nInputTime);
  Serial.println(sInput);
  Serial.println("입력 시간 = " + String(nInputTime * 1e-3) + "sec");
  int nUserScore = compareSentences(sRand, sInput);
  Serial.println("\n현재 스코어 = " + String(nUserScore));
  updateStat(nUserScore, nInputTime);
  printStat();
  Serial.println("==========");
}

void lv3()
{
  String makeRandSentence(int nRandSize)
  {
    String sRandLv3;

    for (int i = 0; i < nRandSize; i++)
    {
      int nRand = random(MAX_TYPE_CHAR);
      int nRandNum = random(MAX_TYPE_INT);
      char ch = toRandChar(nRand);
      char chc = toRandCharCap(nRand);
      int num = toRandInt(nRandNum);
      sRandLv3 = sRandLv2 + num;
    }
    return sRandLv3;
  }
  String sRandLv3 = makeRandSentence(10);
  int nInputTime = 0;

  String sInput = getUserInput(nInputTime);
  Serial.println(sInput);
  Serial.println("입력 시간 = " + String(nInputTime * 1e-3) + "sec");
  int nUserScore = compareSentences(sRand, sInput);
  Serial.println("\n현재 스코어 = " + String(nUserScore));
  updateStat(nUserScore, nInputTime);
  printStat();
  Serial.println("==========");
}


String getSerialInput()
{
  String str;
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    str += c;
    delay(SERIAL_DELAY);
  }
  return str;
}

String scanStr()
{
  while (Serial.available() <= 0);
  return getSerialInput();
}

int scanInt()
{
  String str = scanStr();
  return str.toInt();
}

void clearSerialInput()
{
  while (Serial.available() > 0)
  {
    Serial.read();
    delay(SERIAL_DELAY);

  }
}
//////////
// Random Sentence (난수 문장)
//////////
char toRandChar(int nRand) // 소문자+구두점+대문자
{
  if (nRand <= 25) return (char)(nRand + 'a');
  else if (nRand == 26) return '.';
  else if (nRand == 27) return ',';
  else if (nRand == 28) return '?';
  else if (nRand == 29) return '!';
  else if (nRand == 30) return ' ';
  else return ' ';
}

int toRandInt(int nRandNum) //숫자
{
  for (int i = 0; i < randnum; i++)
  {
    if (nRandNum == i) return i;
  }
}

char toRandCharCap(int nRand)//대문자
{
  if (26 < nRand && nRand <= 51) return (char)(nRand - 26 + 'A');
}


////




////////
// Typing Methods
////////
String getUserInput(int& nInputTime)
{
  nInputTime = 0;
  clearSerialInput();
  int nStartTime = millis();
  String sInput = scanStr();
  int nStopTime = millis();
  nInputTime = nStopTime - nStartTime;
  return sInput;
}

//return score
int compareSentences(String sRand, String sInput)
{ // 문장 비교
  int nScore = 0;
  char wrong = 0;
  int nRandLen = sRandLv1.length();
  int nRandLen = sRandLv2.length();
  int nRandLen = sRandLv3.length();
  int nInputLen = sInput.length();
  int nMinLen = (nRandLen < nInputLen) ? nRandLen : nInputLen;
  Serial.print("오타 = ");

  for (int i = 0; i < nMinLen; i++)
  {
    if (sRandLv1[i] == sInput[i])
    {
      nScore++;
    }
    else if (sRandLv1[i] != sInput[i])
    {
      wrong = sInput[i];
      nWrong++;
      Serial.print(String(wrong) + " ");
      nScore--;
    }


    for (int i = 0; i < nMinLen; i++)
    {
      if (sRandLv2[i] == sInput[i])
      {
        nScore++;
      }
      else if (sRandLv2[i] != sInput[i])
      {
        wrong = sInput[i];
        nWrong++;
        Serial.print(String(wrong) + " ");
        nScore--;
      }

    }

    for (int i = 0; i < nMinLen; i++)
    {
      if (sRandLv3[i] == sInput[i])
      {
        nScore++;
      }
      else if (sRandLv3[i] != sInput[i])
      {
        wrong = sInput[i];
        nWrong++;
        Serial.print(String(wrong) + " ");
        nScore--;
      }

      return nScore - abs(nRandLen - nInputLen);
    }


    //nTotalScore, nTotalInputTime
    void updateStat(int nUserScore, int nInputTime)
    {
      //타자 통계
      nTotalScore += nUserScore;
      nTotalInputTime += nInputTime;
    }

    // nTotalScore, nTotalInputTime

    void printStat()
    {
      //통계 출력
      double typeSpeed = nTotalScore / (double)(nTotalInputTime * 1e-3) * 60.;
      Serial.println("전체 스코어 = " + String(nTotalScore));
      Serial.println("평균 분당 타자수 = " + String(typeSpeed));
      Serial.println("총 오타 개수 = " + String(nWrong));


    }
    void setup() {
      // put your setup code here, to run once:
      initGame();
      Serial.println("1. 소문자 + 구두점");
      Serial.println("2. 소문자 + 구두점 + 대문자");
      Serial.println("3. 소문자 + 구두점 + 대문자 + 숫자");
    }

    void loop() {
      // put your main code here, to run repeatedly:
      ///
      //Serial.println(sRand);
      menu();
      /*
      int nInputTime = 0;

      String sInput = getUserInput(nInputTime);
      Serial.println(sInput);
      Serial.println("입력 시간 = " + String(nInputTime * 1e-3) + "sec");
      int nUserScore = compareSentences(sRand, sInput);
      Serial.println("\n현재 스코어 = " + String(nUserScore));
      updateStat(nUserScore, nInputTime);
      printStat();
      Serial.println("==========");
      */
    }
