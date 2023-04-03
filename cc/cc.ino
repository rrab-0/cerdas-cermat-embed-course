#include <SevSeg.h>

SevSeg sevseg;

// basically the score of team
int startnumberA = 0;
int startnumberB = 100;
int startnumberC = 100;

// Input
// const int KelA = A0;
// const int KelB = A1;
// const int KelC = A2;
// const int add = A3;
// const int sub = A4;
int button = A5;
bool pressed = false;

// Variable
int x = 0;
int y = 0;
int valueKelA = 0;
int valueKelB = 0;
int valueKelC = 0;

volatile bool stateKelA;
volatile bool stateKelB;
volatile bool stateKelC;

void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  // put your setup code here, to run once:
  byte numDigits = 3;
  byte digitPins[] = {4, 3, 2};
  byte segmentPins[] = {7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = true;
  bool leadingZeros = false;
  bool disableDecPoint = true;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
}

void standBy()
{
  sevseg.setChars("abc");
  sevseg.refreshDisplay();
}

void juriNambah(int score)
{
  // +2 until score is 100
  if (score < 100)
  {
    sevseg.setNumber(score);
    sevseg.refreshDisplay();
    score += 2;
  }
  // reset score if score = 100
  if (score == 100)
  {
    score = 0;
  }
  Serial.println(score);
  return score;
}

void juriNambahA()
{
  if (startnumberA < 100)
  {
    sevseg.setNumber(startnumberA);
    sevseg.refreshDisplay();
    startnumberA += 2;
  }
  if (startnumberA == 100)
  {
    startnumberA = 0;
  }
}

void juriNgurangA()
{
  sevseg.setNumber(startnumberA);
  sevseg.refreshDisplay();
  startnumberA -= 2;
}

void juriNambahB()
{
  if (startnumberB < 100)
  {
    sevseg.setNumber(startnumberB);
    sevseg.refreshDisplay();
    startnumberB += 2;
  }
  if (startnumberB == 100)
  {
    startnumberB = 0;
  }
}

void juriNgurangB()
{
  // sevseg.setNumber(startnumberB);
  // sevseg.refreshDisplay();
  startnumberB -= 2;
}

void juriNambahC()
{
  if (startnumberC < 100)
  {
    sevseg.setNumber(startnumberC);
    sevseg.refreshDisplay();
    startnumberC += 2;
  }
  if (startnumberC == 100)
  {
    startnumberC = 0;
  }
}

void juriNgurangC()
{
  // sevseg.setNumber(startnumberC);
  // sevseg.refreshDisplay();
  startnumberC -= 2;
}

// displays team and the current score they have
void displayTimA()
{
  char buffer[5];
  char teamA[] = "a";
  sprintf(buffer, "%s%d", teamA, startnumberA);
  sevseg.setChars(buffer);
  sevseg.refreshDisplay();
}

void displayTimB()
{
  char bufferB[5];
  char teamB[] = "a";
  sprintf(bufferB, "%s%d", teamB, startnumberB);
  sevseg.setChars(bufferB);
  sevseg.refreshDisplay();
}

void displayTimC()
{
  char bufferC[5];
  char teamC[] = "c";
  sprintf(bufferC, "%s%d", teamC, startnumberC);
  sevseg.setChars(bufferC);
  sevseg.refreshDisplay();
}

const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

void loop()
{
  unsigned long currentTime = millis();
  bool state = digitalRead(button);
  // standBy();
  displayTimA();
  // if pressed would do +2
  if (state == pressed)
  {
    juriNambahA();
    Serial.println(startnumberA);
    // Serial.println(score);
    // juriNambahA();
    // juriNgurangB();
    while (digitalRead(button) == pressed)
    {
      // do nothing
    }
    // Serial.println(startnumberA);
    // Serial.println(startnumberB);
  }
}