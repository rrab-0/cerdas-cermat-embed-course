#include <SevSeg.h>

SevSeg sevseg;

// basically the score of each team
int startnumberA = 0;
int startnumberB = 5;
int startnumberC = 100;

// Input
int button = A5;
int buttonB = A0;
int buttonTambah = A1;
int buttonKurang = A2;
bool pressed = false;

// check if team is wrong
bool jawabanA = true;
bool jawabanB = true;
bool jawabanC = true;

int tim = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonTambah, INPUT_PULLUP);
  pinMode(buttonKurang, INPUT_PULLUP);

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
  char bufferStandBy[5];
  char teamA[] = "a";
  char teamB[] = "b";
  char teamC[] = "c";
  if (jawabanA == false)
  {
    teamA[] = "0";
  }
  if (jawabanB == false)
  {
    teamB[] = "0";
  }
  if (jawabanC == false)
  {
    teamC[] = "0";
  }
  sprintf(bufferStandBy, "%s%s%s", teamA, teamB, teamC);
  sevseg.setChars(bufferStandBy);
  sevseg.refreshDisplay();
}

void displaysTeamsScores2Sec()
{
  // put this something bool in loop
  bool something = true;
  while (something == true)
  {
    displayTeam("A");
    // 2 sec delay
    displayTeam("B");
    // 2 sec delay
    displayTeam("C");
    // 2 sec delay
  }
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

void juriNgurang(int tim)
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
  if (initialScore == 0)
  {
    initialScore = 0;
  }

  // check which team juri is adding
  if (tim == 1)
  {
    startnumberA -= initialScore;
  }
  else if (tim == 2)
  {
    startnumberB -= initialScore;
  }
  else if (tim == 3)
  {
    startnumberC -= initialScore;
  }
}

void juriNambahKurangA(int mathA, int tim)
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

void displayTeam(char teamABC[])
{
  if (teamABC == "A")
  {
    char buffer[5];
    char teamA[] = "a";
    sprintf(buffer, "%s%d", teamA, startnumberA);
    sevseg.setChars(buffer);
    sevseg.refreshDisplay();
  }
  else if (teamABC == "B")
  {
    char bufferB[5];
    char teamB[] = "b";
    sprintf(bufferB, "%s%d", teamB, startnumberB);
    sevseg.setChars(bufferB);
    sevseg.refreshDisplay();
  }
  else if (teamABC == "C")
  {
    char bufferC[5];
    char teamC[] = "c";
    sprintf(bufferC, "%s%d", teamC, startnumberC);
    sevseg.setChars(bufferC);
    sevseg.refreshDisplay();
  }
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
  bool statetambah = digitalRead(buttonTambah);
  bool statekurang = digitalRead(buttonKurang);
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
  int tim = 0;

  if (state == pressed)
  {
    timB_State = false;
    while (timA_State == true)
    {
      tim = 1;
      displayTeam("A");
      Serial.println("A");

      // nambah score kalo bener
      if (digitalRead(buttonTambah) == pressed)
      {

        juriNambah(tim);
      }

      // ngurang score kalo salah, and goes to standby
      // here, standby displays only teams that havent answered
      else if (digitalRead(buttonKurang) == pressed)
      {
        jawabanA = false;
        tim = 1;
        juriNgurang(tim);
        // standby();
      }

      if (digitalRead(buttonB) == pressed)
      {
        timA_State = false;
        while (digitalRead(buttonB) == pressed)
        {
          // do nothing
        }
        break;
      }
    }
    while (digitalRead(button) == pressed)
    {
      // do nothing
    }
  }

  if (stateB == pressed)
  {
    tim = 2;
    timA_State = false;
    while (timB_State == true)
    {
      displayTeam("B");
      Serial.println("B");

      // nambah score kalo bener
      if (digitalRead(buttonTambah) == pressed)
      {
        juriNambah(tim);
      }

      // ngurang score kalo salah, and goes to standby
      // here, standby displays only teams that havent answered
      else if (digitalRead(buttonKurang) == pressed)
      {
        juriNgurang(tim);
        // standby();
      }

      if (digitalRead(button) == pressed)
      {
        timB_State = false;
        while (digitalRead(button) == pressed)
        {
          // do nothing
        }
      }
    }
    while (digitalRead(buttonB) == pressed)
    {
      // do nothing
    }
  }
}