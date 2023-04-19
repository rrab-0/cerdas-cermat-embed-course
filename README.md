# cerdas-cermat/quiz system with arduino

A one week team-based project for the course 'Embedded Systems' consists of 3 people. 

I'm responsible for :
- Developing the prototype in tinkercad and breadboard
- Designing and developing the software that powers the system

Components used :

- 1 Arduino Uno R3 (used on breadboard)
- 1 Arduino Nano (used on pcb)
- 6 Pushbutton
- 3 Arduino Uno R3
- 10 Arduino Uno R3

Tinkercard version :

![Tinkercad sketch](https://github.com/rrab-0/cerdas-cermat-quiz-system/blob/master/img-for-readme/tinkercad-cerdas-cermat-embed.png)

Breadboard version :

![Breadboard sketch](https://github.com/rrab-0/cerdas-cermat-quiz-system/blob/master/img-for-readme/breadboard-sketch.jpeg)

PCB version :

![PCB version](https://github.com/rrab-0/cerdas-cermat-quiz-system/blob/master/img-for-readme/pcb-ver.jpeg)

How it works :

- There is 3 teams A/B/C and a "judge" to add/subtract score and also diplays all team's current score
- The yellow buttons are to show score of team A or B or C (from left to right)
  - ex: if A is pressed would output A00 which means its A teams time to answer the 'quiz' question and that they have the score of 0
- The red buttons are for the "judge"
  - left button is for displaying all the teams (output would be ABC on display) could also act as a standby button to reset position (from pos A01 back to ABC hence "standby" button)
    - if pressed again would output all teams score's for 2 seconds each (ex : A00 -> B10 -> C03)
  - middle button is for adding score by 2
  - right button is for subtracting score by 1
- If an answer is wrong their display would be changed to '-' ex: if A is wrong then -BC as opposed to ABC
