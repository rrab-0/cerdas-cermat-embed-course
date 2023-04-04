# TODOs ,

- need millis() to work for blinking
  //- need to simplify displayTim() and juriNambah() for more performance
  //- need to display team if a team pressed first, could use booleans
  //- to set only standby button is active, nest the if logics of other buttons inside standby button logic

# What i need to make ,

- cerdas cermat system. 6 buttons, 3 for peserta and 3 for juri.

- 3 peserta buttons displays current score of their team

- 3 juri buttons does the following :
  - 1. Button one, if answer is correct +2 score then displays score
  - 2. Button two, if answer is not correct -1 score
    - (need to do this) then displays score for 2 seconds
    - then goes back to standBy() but only displays team that haven't answered yet ( because one of them answers wrong so its not displayed anymore )
  - 3. Button three, standBy()
    - if pressed once will reset status of all peserta buttons to standBy(). ex : if team A is answering which means display is 'Axx' it will return to 'ABC'.
    - if pressed again after pressing once, will diplay current scores of teams
      - (need to do this) diplays current scores of each team for 2 secs then goes back to standBy() or teams that have a right to answer a question.

# How the game works,

- First, all score is 0
- only active button is button for standby() from juri
- standby() is displaying teams that have a right to answer a question. ex: 'abc'. also, (need to do this) the display blinks twice in one second.
- if a team pressed first to answer a question, other 2 buttons are disabled. then displays team name and current score of team ex: 'Axx' or 'C00' or 'B10', etc
  - if answer is correct, +2
  - if answer is not correct, -1 and goes back to standby() and only diplays teams that haven't answered yet.

keep in mind that :

- standby()
  - if pressed once will return to standby() mode, ex : if team A is answering which means display is 'Axx' it will return to 'ABC'.
  - if pressed after pressing once will display all current team scores for 2 seconds each team then goes back to standby().
