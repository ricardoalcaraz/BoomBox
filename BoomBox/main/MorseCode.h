#ifndef MorseCode_h
#define MorseCode_h

#include "Arduino.h"
#include "Observer.h"
#include "LED.h"
/*------------Rules for Morse Code-----------------
There are rules to help people distinguish dots from dashes in Morse code.
   1. The length of a dot is 1 time unit.
   2. A dash is 3 time units.
   3. The space between symbols (dots and dashes) of the same letter is 1 time unit.
   4. The space between letters is 3 time units.
   5. The space between words is 7 time units.
Morse Code Alphabet
A   .-
B   -...
C   -.-.
D   -..
E   .
F   ..-.
G   --.
H   ....
I   ..
J   .---
K   -.-
L   .-..
M   --
N   -.
O   ---
P   .--.
Q   --.-
R   .-.
S   ...
T   -
U   ..-
V   ...-
W   .--
X   -..-
Y   -.--
Z   --..
*/
class MorseCode : public Observer {
  public:
    MorseCode(uint8_t code, LED*);
    void receiveDataFromSubject( Subject* );
  private:
    LED* led;
    char* convertMorse( char morseWord ); 
    char word1[4];
    char word2[4];
    char* morse1[4];
    char* morse2[4];
    void nextState();
    char currentState1;
    char currentState2;
    uint8_t timeUnits1;
    uint8_t timeUnits2;
};



/*
char* convertMorse( char morseWord ) {
  static int j = 0;
  char* morse;
    switch (morseWord) {
      case 'a': morse = ".-";
                break;
      case 'e': morse = ".";
                break;
      case 'i': morse = "..";
                break;
      case 'p': morse = ".--.";
                break;
      case 'r': morse = ".-.";
                break;                
      }
  return morse;
}

void morseBlink() {
  static uint8_t counter = 0;
  if(counter == currentTimeUnits) {
    digitalWrite(morseLED1, LOW);
    counter = 0;
    stateChanged = true;
  }
  counter++;
}


void morseCodeInit() {
  pinMode(morseLED1, OUTPUT);
  pinMode(morseLED2, OUTPUT);
  digitalWrite(morseLED2, HIGH);
  morseTimer.begin(morseBlink, 750000);
  for( int i = 0; i < 4; i++ ) {
    morse1[i] = convertMorse(morseWord1[i]);
  }
  for( int i = 0; i < 4; i++ ) {
    morse2[i] = convertMorse(morseWord2[i]);
  }
}

/*
Space between symbols = *
Space between letters = ^
Space between words = #
*/
/*
State machine will keep track of which letter it is on and
since each letter has it's own symbols to keep track of
the index of the symbols will be kept track of as well.

This function should only run when the state has changed
since it changes how many time units will pass before this 
function is ran again. 
*/
/*
void nextMorseState() {
  noInterrupts();
  static uint8_t letterIndex1 = 0;
  static uint8_t letterIndex2 = 0;
  static uint8_t symbolIndex1 = 0; 
  static uint8_t symbolIndex2 = 0;
  static char* currentLetter1 = morse1[0];
  static char* currentLetter2 = morse2[0];
  static char currentSymbol1 = currentLetter1[0]; 
  static char currentSymbol2 = currentLetter2[0];
  static bool intervalPassed = true;
  
  switch( currentSymbol1 ) {
    case '#':
              letterIndex1 = 0;
              symbolIndex1 = 0;
              currentLetter1 = morse1[letterIndex1];
              break;
    case '^': 
               symbolIndex1 = 0;
               letterIndex1++;
               currentLetter1 = morse1[letterIndex1];
               break;
    case '*':
              symbolIndex1++;
              break;
  }
  if( symbolIndex1 > 4 || currentLetter1[symbolIndex1] == 0 ) {
    symbolIndex1 = 0; 
    currentSymbol1 = currentLetter1[symbolIndex1];
  }
  if( currentSymbol1 == '.' ) {
    currentTimeUnits = 1;
    digitalWrite(morseLED1, HIGH);
  } else if( currentSymbol1 == '-' ) {
    currentTimeUnits == 3;
    digitalWrite(morseLED1, HIGH);
  } else if( currentSymbol1 == '*') {
    currentTimeUnits = 1;
    digitalWrite(morseLED1, LOW);
  } else if( currentSymbol1 == '#') {
    currentTimeUnits = 7;
    digitalWrite(morseLED1, LOW);
  }

  interrupts();
}
*/
#endif
