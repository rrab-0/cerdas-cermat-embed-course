#include <SevSeg.h>

SevSeg sevseg;

// basically the score of each team
int startnumberA = 0;
int startnumberB = 5;
int startnumberC = 10;

int tim = 0;

// Input
int buttonA = A0;
int buttonB = A1;
int buttonC = A2;
int buttonTambah = A3;
int buttonKurang = A4;
int buttonStandBy = A5;

// check for input
bool pressed = false;

// check if team is wrong
bool jawabanA = true;
bool jawabanB = true;
bool jawabanC = true;

void setup()
{
  Serial.begin(9600);

  // peserta
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);

  // juri
  pinMode(buttonTambah, INPUT_PULLUP);
  pinMode(buttonKurang, INPUT_PULLUP);
  pinMode(buttonStandBy, INPUT_PULLUP);

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
    char teamA = "a";
    char teamB = "b";
    char teamC = "c";
    if (jawabanA == false)
    {
      teamA = "0";
    }
    if (jawabanB == false)
    {
      teamB = "0";
    }
    if (jawabanC == false)
    {
      teamC = "0";
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
  unsigned long currentTime = millis();
  bool timA_State = true;
  bool timB_State = true;
  bool timC_State = true;
  bool standby_State = true;
  bool stateA = digitalRead(buttonA);
  bool stateB = digitalRead(buttonB);
  bool stateC = digitalRead(buttonC);
  bool stateTambah = digitalRead(buttonTambah);
  bool stateKurang = digitalRead(buttonKurang);
  bool stateStandBy = digitalRead(buttonStandBy);
  // if (standByState == false)
  // {
  //   standBy();
  // }
  // else if (stateA == pressed )
  //   {
  //     // displayTimA();
  //     while (digitalRead(buttonA) == pressed)
  //     {
  //       // do nothing
  //     }
  //   }
  //standBy();
  if (stateStandBy == pressed)
  {
    tim = 0;
    timA_State = true;
    timB_State = true;
    timC_State = true;

    while (standby_State == true)
    {
      return;
    }

    if (digitalRead(buttonA) == pressed)
    {
      standby_State = false;
      while (digitalRead(buttonA) == pressed)
      {
        // do nothing
      }
    }
    else if (digitalRead(buttonB) == pressed)
    {
      standby_State = false;
      while (digitalRead(buttonB) == pressed)
      {
        //  do nothing
      }
    }
    else if (digitalRead(buttonC) == pressed)
    {
      standby_State = false;
      while (digitalRead(buttonC) == pressed)
      {
        // do nothing
      }
    }

    while (digitalRead(buttonStandBy) == pressed)
    {
      // do nothing
    }
  }

  if (stateA == pressed)
  {
    tim = 1;
    timB_State = false;
    timC_State = false;
    while (timA_State == true)
    {
      displayTeam("A");
      Serial.println("A");

      // nambah score kalo bener
      if (digitalRead(buttonTambah) == pressed)
      {
        juriNambah(tim);
        while (digitalRead(buttonTambah) == pressed)
        {
          // do nothing
        }
      }
      // ngurang score kalo salah, and goes to standby
      // here, standby displays only teams that havent answered
      else if (digitalRead(buttonKurang) == pressed)
      {
        jawabanA = false;
        // tim = 1;
        juriNgurang(tim);
        while (digitalRead(buttonKurang) == pressed)
        {
          // do nothing
        }
        // standby();
      }

      if (digitalRead(buttonStandBy) == pressed)
      {
        timA_State = false;
        while (digitalRead(buttonStandBy) == pressed)
        {
          // do nothing
        }
      }
    }
    while (digitalRead(buttonA) == pressed)
    {
      // do nothing
    }
  }

  if (stateB == pressed)
  {
    tim = 2;
    timA_State = false;
    timC_State = false;
    while (timB_State == true)
    {
      displayTeam("B");
      Serial.println("B");

      // nambah score kalo bener
      if (digitalRead(buttonTambah) == pressed)
      {
        juriNambah(tim);
        while (digitalRead(buttonTambah) == pressed)
        {
          // do nothing
        }
      }
      // ngurang score kalo salah, and goes to standby
      // here, standby displays only teams that havent answered
      else if (digitalRead(buttonKurang) == pressed)
      {
        juriNgurang(tim);
        // standby();
        while (digitalRead(buttonKurang) == pressed)
        {
          // do nothing
        }
      }

      if (digitalRead(buttonStandBy) == pressed)
      {
        timB_State = false;
        while (digitalRead(buttonStandBy) == pressed)
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

  if (stateC == pressed)
  {
    tim = 3;
    timA_State = false;
    timB_State = false;
    while (timC_State == true)
    {
      displayTeam("C");
      Serial.println("C");

      // nambah score kalo bener
      if (digitalRead(buttonTambah) == pressed)
      {
        juriNambah(tim);
        while (digitalRead(buttonTambah) == pressed)
        {
          // do nothing
        }
      }
      // ngurang score kalo salah, and goes to standby
      // here, standby displays only teams that havent answered
      else if (digitalRead(buttonKurang) == pressed)
      {
        juriNgurang(tim);
        // standby();
        while (digitalRead(buttonKurang) == pressed)
        {
          // do nothing
        }
      }

      if (digitalRead(buttonStandBy) == pressed)
      {
        timC_State = false;
        while (digitalRead(buttonStandBy) == pressed)
        {
          // do nothing
        }
      }
    }
    while (digitalRead(buttonC) == pressed)
    {
      // do nothing
    }
  }
}