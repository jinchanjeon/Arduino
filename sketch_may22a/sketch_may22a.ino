#define PORT_RAND (A1)
#define SERIAL_RATE (9600)
#define SERIAL_DELAY (50)
#define NUM (10)
#define SPECIAL 5
#define MAX_TYPE_CHAR (26 * 2 + SPECIAL + NUM)


int c;
int nTotalScore = 0; //합산 스코어
long nTotalInputTime = 0; // 총 입력 시간 (ms)

///////////////////////////
// 초기화 부분 (타자 초기화)
///////////////////////////
void initRand(){
  int nVolt = analogRead(PORT_RAND);
  randomSeed(nVolt); // 난수를 초기화
}

void initGame(){  // 타자 초기화
  Serial.begin(SERIAL_RATE);
  initRand();
}

///////////////////////////
// 메뉴 선택 부분
///////////////////////////
void ChoiceMain(){
  if(Serial.available()){
    char c = Serial.read();
    if (c == '1'){
      level1();
      }
    else if (c == '2'){
      level2();
    }
    else if (c == '3'){
      level3();
    }
    else if (c == '4'){
      level4();
    }
    else if (c == '5'){
      level5();
    }
    else if (c == '6'){
      level6();
    }
     else if (c == '7'){
      level7();
    }
    else if (c == '0'){
      Serial.println("==============게임 설명==================");
      Serial.println("이성훈의 타자게임에 오신 것을 환영합니다.");
      Serial.println("난이도 별로 총 10번의 게임이 진행이됩니다."); 
      Serial.println("랜덤으로 나오는 문장과 같은 문장을 입력해야 점수가 주어집니다.");
      Serial.println("문장에서 한 문자 당 2점씩 득점이고 틀릴 시에도 2점씩 감점됩니다." );
      Serial.println("게임이 종료되면 최종 스코어와 분당 평균 타자 속도를 알 수 있습니다.");
      Serial.println("그럼 이제 난이도를 선택하고 게임을 즐기시면 됩니다 ~ ^^");
       Serial.println("========================================");
    } 
  }
}
////////////////////
//문제 출제 부분/////
///////////////////
void level1(){ //영어 소문자
  for (int i =0; i < 10; i++){ //5번의 게임을 진행
    int nTotalScore = 0; //합산 스코어
    String sRand = makeRandSmall(10);
    Serial.println(sRand);
    int nInputTime = 0;
    String sInput = getUserInput(nInputTime);
    Serial.println(sInput);
    Serial.println("입력 시간 = " + String(nInputTime*1e-3) + " sec");
    int nUserScore = compareSentences(sRand, sInput);
    Serial.println("획득 스코어 = " + String(nUserScore));
    updateStat(nUserScore, nInputTime);
    Serial.println("=======================");
    }
  Serial.println("**********게임 종료************");
  printStat(); //게임이 모두 끝난 후 전체스코어와 평균 분당 타자수를 출력
  Serial.end(); //게임이 끝난 후 시리얼을 종료 시킴
 }

void level2(){ // 영어 대문자
  for (int i =0; i < 10; i++){ //5번의 게임을 진행
     int nTotalScore = 0; //합산 스코어
     String sRand = makeRandBig(10);
     Serial.println(sRand);
     int nInputTime = 0;
     String sInput = getUserInput(nInputTime);
     Serial.println(sInput);
     Serial.println("입력 시간 = " + String(nInputTime*1e-3) + " sec");
     int nUserScore = compareSentences(sRand, sInput);
     Serial.println("획득 스코어 = " + String(nUserScore));
     updateStat(nUserScore, nInputTime);
     Serial.println("=======================");
      }
  Serial.println("**********게임 종료************");
  printStat(); //게임이 모두 끝난 후 전체스코어와 평균 분당 타자수를 출력
  Serial.end(); //게임이 끝난 후 시리얼을 종료 시킴
}

void level3(){ // 숫자
 for (int i =0; i < 10; i++){ //5번의 게임을 진행
     int nTotalScore = 0; //합산 스코어
     String sRand = makeRandNum(10);
     Serial.println(sRand);
     int nInputTime = 0;
     String sInput = getUserInput(nInputTime);
     Serial.println(sInput);
     Serial.println("입력 시간 = " + String(nInputTime*1e-3) + " sec");
     int nUserScore = compareSentences(sRand, sInput);
     Serial.println("획득 스코어 = " + String(nUserScore));
     updateStat(nUserScore, nInputTime);
     Serial.println("=======================");
      }
  Serial.println("**********게임 종료************");
  printStat(); //게임이 모두 끝난 후 전체스코어와 평균 분당 타자수를 출력
  Serial.end(); //게임이 끝난 후 시리얼을 종료 시킴
}

void level4(){ // 소문자 + 대문자
 for (int i =0; i < 10; i++){ //5번의 게임을 진행
     int nTotalScore = 0; //합산 스코어
     String sRand = makeRandBnS(10);
     Serial.println(sRand);
     int nInputTime = 0;
     String sInput = getUserInput(nInputTime);
     Serial.println(sInput);
     Serial.println("입력 시간 = " + String(nInputTime*1e-3) + " sec");
     int nUserScore = compareSentences(sRand, sInput);
     Serial.println("획득 스코어 = " + String(nUserScore));
     updateStat(nUserScore, nInputTime);
     Serial.println("=======================");
      }
  Serial.println("**********게임 종료************");
  printStat(); //게임이 모두 끝난 후 전체스코어와 평균 분당 타자수를 출력
  Serial.end(); //게임이 끝난 후 시리얼을 종료 시킴
}

void level5(){ // 소문자 + 숫자
 for (int i =0; i < 10; i++){ //5번의 게임을 진행
     int nTotalScore = 0; //합산 스코어
     String sRand = makeRandSnN(10);
     Serial.println(sRand);
     int nInputTime = 0;
     String sInput = getUserInput(nInputTime);
     Serial.println(sInput);
     Serial.println("입력 시간 = " + String(nInputTime*1e-3) + " sec");
     int nUserScore = compareSentences(sRand, sInput);
     Serial.println("획득 스코어 = " + String(nUserScore));
     updateStat(nUserScore, nInputTime);
     Serial.println("=======================");
      }
  Serial.println("**********게임 종료************");
  printStat(); //게임이 모두 끝난 후 전체스코어와 평균 분당 타자수를 출력
  Serial.end(); //게임이 끝난 후 시리얼을 종료 시킴
}

void level6(){ // 대문자 + 숫자
 for (int i =0; i < 10; i++){ //5번의 게임을 진행
     int nTotalScore = 0; //합산 스코어
     String sRand = makeRandBnN(10);
     Serial.println(sRand);
     int nInputTime = 0;
     String sInput = getUserInput(nInputTime);
     Serial.println(sInput);
     Serial.println("입력 시간 = " + String(nInputTime*1e-3) + " sec");
     int nUserScore = compareSentences(sRand, sInput);
     Serial.println("획득 스코어 = " + String(nUserScore));
     updateStat(nUserScore, nInputTime);
     Serial.println("=======================");
      }
  Serial.println("**********게임 종료************");
  printStat(); //게임이 모두 끝난 후 전체스코어와 평균 분당 타자수를 출력
  Serial.end(); //게임이 끝난 후 시리얼을 종료 시킴
}


void level7(){ // 소문자 + 대문자 + 숫자 + 구두점
 for (int i =0; i < 10; i++){ //5번의 게임을 진행
     int nTotalScore = 0; //합산 스코어
     String sRand = makeRandAll(10);
     Serial.println(sRand);
     int nInputTime = 0;
     String sInput = getUserInput(nInputTime);
     Serial.println(sInput);
     Serial.println("입력 시간 = " + String(nInputTime*1e-3) + " sec");
     int nUserScore = compareSentences(sRand, sInput);
     Serial.println("획득 스코어 = " + String(nUserScore));
     updateStat(nUserScore, nInputTime);
     Serial.println("=======================");
      }
  Serial.println("**********게임 종료************");
  printStat(); //게임이 모두 끝난 후 전체스코어와 평균 분당 타자수를 출력
  Serial.end(); //게임이 끝난 후 시리얼을 종료 시킴
}


///////////////////////////
//랜덤한 소문자로 이루어진 문장
///////////////////////////
char toRandSmall(int nRand){
  if (nRand <= 25) return(char)(nRand + 'a');
}

String makeRandSmall(int nRandSize){ // 난수 문장 발생기
  String sRand;
  for (int i = 0; i < nRandSize; i++) { //반복
      int nRand = random(MAX_TYPE_CHAR); //0~31까지 랜덤으로
      char ch = toRandSmall(nRand); // int를 char로 바꿈
      sRand += ch;
  }
  return sRand;
}

///////////////////////////
//랜덤한 대문자로 이루어진 문장
///////////////////////////
char toRandBig(int nRand){
  if (25 < nRand && nRand <= 51)return(char)(nRand - 26 + 'A');
}

String makeRandBig(int nRandSize){ // 난수 문장 발생기
  String sRand;
  for (int i = 0; i < nRandSize; i++) { //반복
      int nRand = random(MAX_TYPE_CHAR); //0~31까지 랜덤으로
      char ch = toRandBig(nRand); // int를 char로 바꿈
      sRand += ch;
  }
  return sRand;
}

///////////////////////////
//랜덤한 숫자로 이루어진 문장
///////////////////////////
char toRandNum(int nRand){
  if (51< nRand && nRand < 61)return(char)(nRand - 52 + '0');
}

String makeRandNum(int nRandSize){ // 난수 문장 발생기
  String sRand;
  for (int i = 0; i < nRandSize; i++) { //반복
      int nRand = random(MAX_TYPE_CHAR); //0~31까지 랜덤으로
      char ch = toRandNum(nRand); // int를 char로 바꿈
      sRand += ch;
  }
  return sRand;
}

///////////////////////////
//랜덤한 소문자+대문자로 이루어진 문장
///////////////////////////
char toRandBnS(int nRand){
 if (nRand <= 25) return(char)(nRand + 'a');
  else if (25 < nRand && nRand <= 51)return(char)(nRand - 26 + 'A');
}

String makeRandBnS(int nRandSize){ // 난수 문장 발생기
  String sRand;
  for (int i = 0; i < nRandSize; i++) { //반복
      int nRand = random(MAX_TYPE_CHAR); //0~31까지 랜덤으로
      char ch = toRandBnS(nRand); // int를 char로 바꿈
      sRand += ch;
  }
  return sRand;
}

///////////////////////////
//랜덤한 소문자+숫자로 이루어진 문장
///////////////////////////
char toRandSnN(int nRand){
  if (nRand <= 25) return(char)(nRand + 'a');
  else if (25 < nRand && nRand <=35)return(char)(nRand - 25 + '0');
}

String makeRandSnN(int nRandSize){ // 난수 문장 발생기
  String sRand;
  for (int i = 0; i < nRandSize; i++) { //반복
      int nRand = random(MAX_TYPE_CHAR); //0~31까지 랜덤으로
      char ch = toRandBnN(nRand); // int를 char로 바꿈
      sRand += ch;
  }
  return sRand;
}

///////////////////////////
//랜덤한 대문자+숫자로 이루어진 문장
///////////////////////////
char toRandBnN(int nRand){
  if (25 < nRand && nRand <= 51)return(char)(nRand - 26 + 'A');
  else if (51< nRand && nRand < 61)return(char)(nRand - 52 + '0');
}

String makeRandBnN(int nRandSize){ // 난수 문장 발생기
  String sRand;
  for (int i = 0; i < nRandSize; i++) { //반복
      int nRand = random(MAX_TYPE_CHAR); //0~31까지 랜덤으로
      char ch = toRandBnN(nRand); // int를 char로 바꿈
      sRand += ch;
  }
  return sRand;
}

///////////////////////////
//랜덤한 소문자+대문자+숫자+구두점으로 이루어진 문장
///////////////////////////
char toRandAll(int nRand){
  if (nRand <= 25) return(char)(nRand + 'a');
  else if (25 < nRand && nRand <= 51)return(char)(nRand - 26 + 'A');
  else if (51< nRand && nRand < 61)return(char)(nRand - 52 + '0');
  else if (nRand == 62) return '.';
  else if (nRand == 63) return ',';
  else if (nRand == 64) return '!';
  else if (nRand == 65) return '?';
  else if (nRand == 66) return ' ';
  else return ' ';
}

String makeRandAll(int nRandSize){ // 난수 문장 발생기
  String sRand;
  for (int i = 0; i < nRandSize; i++) { //반복
      int nRand = random(MAX_TYPE_CHAR); //
      char ch = toRandAll(nRand); // int를 char로 바꿈
      sRand += ch;
  }
  return sRand;
}


//////////////////////
///////사용자 입력 받기
/////////////////////


String getSerialInput() { //문자열을 입력받는 함수
  String str; // length() == 0
  while (Serial.available() > 0) // Data input
  {
    char c = Serial.read();
    str += c;

    delay(SERIAL_DELAY);
  }
  return str;
}

String scanStr() { //문자열을 입력받는 함수
  while (Serial.available() <= 0); //정수가 입력될 때까지 기다린다.
  return getSerialInput();
}

int scanInt(){
  String str = scanStr();
  return str.toInt(); //받은 문자를 정수로 바꾸는 함수
}

void clearSerialInput(){
  while (Serial.available() > 0) // Data input
  {
    char c = Serial.read();
    delay(SERIAL_DELAY);
  }
}

////////////
//타이핑 메소드
////////////

String getUserInput(int& nInputTime) { // 사용자 입력과 동시에 입력 시간 측정
  nInputTime = 0;
  clearSerialInput();
  int nStartTime = millis();
  String sInput = scanStr();
  int nStopTime = millis();
  nInputTime = nStopTime - nStartTime; // in msec
  return sInput;
}

//스코어를 반환해주는 함수
int compareSentences(String sRand, String sInput) { //문장을 비교하는 부분
  int nScore = 0;
  int nRandLen = sRand.length();
  int nInputLen = sInput.length();
  int nMinLen = (nRandLen < nInputLen) ? nRandLen : nInputLen;
  for (int i = 0; i < nMinLen; i++){
    if (sRand[i] == sInput[i]) nScore++;
    else nScore--;
  }
  return nScore - abs(nRandLen - nInputLen);
}


//종합 스코어랑 종합 시간을 통계처리해야함
void updateStat(int nUserScore, int nInputTime){ // 타자 통계
  nTotalScore += nUserScore;
  nTotalInputTime += nInputTime;
  
}

//종합스코어 종합시간 출력
void printStat(){
  double typeSpeed = nTotalScore /(double)(nTotalInputTime*1e-3)*60.; //분당 타자수
  Serial.println("전체 스코어 = " + String(nTotalScore));
  Serial.println("평균 분당 타자수 = " + String(typeSpeed));
}


void setup() {
  // put your setup code here, to run once:
  initGame();
  Serial.println("타자 게임에 오신 것을 환영합니다");
  Serial.println("게임 설명서 : 0 ");
  Serial.println("난이도를 설정하세요.");
  Serial.println("|난이도 1 : 1. 소문자만    | 2. 대문자만       | 3. 숫자만        |" );
  Serial.println("|난이도 2 : 4. 소 + 대문자 | 5. 소문자 + 숫자  | 6. 대문자 + 숫자  |" );
  Serial.println("|난이도 3 : 7. 소문자 + 대문자 + 숫자 + 구두점                    |" );
}


void loop() {
  // put your main code here, to run repeatedly:
  ChoiceMain();
}
