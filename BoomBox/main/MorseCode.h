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

/*This class registers to a timer as an observer and will be updated whenever the timer ticks down
 *Will display 4 letters words in morse code onto two leds 
 *and will update the external led class*/
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
    void nextState1();
    void nextState2();
    char currentState1;
    char currentState2;
    uint8_t timeUnits1;
    uint8_t timeUnits2;
};

#endif
