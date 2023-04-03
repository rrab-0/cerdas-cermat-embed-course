#include <SevSeg.h>

SevSeg sevseg;

long startnumber = 0;

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

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  // put your setup code here, to run once:
  byte numDigits = 3;
  byte digitPins[] = { 4, 3, 2 };
  byte segmentPins[] = { 7, 8, 9, 10, 11, 12, 13 };
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = true;
  bool leadingZeros = false;
  bool disableDecPoint = true;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  // sevseg.setBrightness(-60);
}

void juriNambah() {
}

void juriNgurang() {
}

void loop() {
  bool state = digitalRead(button);

  sevseg.setNumber(startnumber);
  sevseg.refreshDisplay();

  // if pressed would do +2
  if (state == pressed) {
    if (startnumber < 100) {
      sevseg.setNumber(startnumber);
      sevseg.refreshDisplay();
      startnumber += 2;
    }
    while (digitalRead(button) == pressed) {
      // do nothing
      Serial.println(startnumber);
    }
  }
}