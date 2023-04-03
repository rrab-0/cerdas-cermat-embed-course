#include <SevSeg.h>

SevSeg sevseg;

// basically the score of each team
int startnumberA = 0;
int startnumberB = 5;
int startnumberC = 100;

// Input
int button = A5;
int buttonB = A0;
bool pressed = false;

void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);

  // setup for SevSeg.h
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

void juriNambah(int tim)
{
  int initialScore = 0;
  // +2 until score is 100
  if (initialScore < 100)
  {
    sevseg.setNumber(initialScore);
    sevseg.refreshDisplay();
    initialScore += 2;
  }
  // reset initialScore if initialScore = 100
  if (initialScore == 100)
  {
    initialScore = 0;
  }

  // check which team juri is adding
  if (tim == 1)
  {
    startnumberA += initialScore;
  }
  else if (tim == 2)
  {
    startnumberB += initialScore;
  }
  else if (tim == 3)
  {
    startnumberC += initialScore;
  }
}

void juriNambahKurangA(int mathA)
{
  if (mathA == 1)
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
  else if (mathA == 2)
  {
    sevseg.setNumber(startnumberA);
    sevseg.refreshDisplay();
    startnumberA -= 2;
  }
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
  char teamB[] = "b";
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
  bool timA_State = true;
  bool timB_State = true;
  unsigned long currentTime = millis();
  bool state = digitalRead(button);
  bool stateB = digitalRead(buttonB);
  // if (standByState == false)
  // {
  //   standBy();
  // }
  // else if (state == pressed )
  //   {
  //     // displayTimA();
  //     while (digitalRead(button) == pressed)
  //     {
  //       // do nothing
  //     }
  //   }

  if (state == pressed)
  {
    timB_State = false;
    while (timA_State == true)
    {
      Serial.println("A");
      if (digitalRead(buttonB) == pressed)
      {
        timA_State = false;
        while (digitalRead(buttonB) == pressed)
        {
          // do nothing
        }
        break;
      }
      displayTimA();
    }
    while (digitalRead(button) == pressed)
    {
      // do nothing
    }
  }

  if (stateB == pressed)
  {
    timA_State = false;
    while (timB_State == true)
    {
      Serial.println("B");
      if (digitalRead(button) == pressed)
      {
        timB_State = false;
        while (digitalRead(button) == pressed)
        {
          // do nothing
        }
      }
      displayTimB();
    }
    while (digitalRead(buttonB) == pressed)
    {
      // do nothing
    }
  }
}