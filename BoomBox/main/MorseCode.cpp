#include "MorseCode.h"

const char pear[4] = {'p','e','a','r'};
const char pair[4] = {'p','a','i','r'};
const char pare[4] = {'p','a','r','e'};
//Constructor
/*Picks the words that will be displayed onto the two
 *leds depending on the input code then updates the led value
 *in the led class*/
MorseCode::MorseCode( LED* led) {

  this->led = led;
}

/* Inputs a random number from trng to assign a random morse code word
 * Converts those words to morse code
 */
void MorseCode::init( uint8_t code1, uint8_t code2 ) {
    // Used to randomly determine what morse code to display
    morseCode1 = code1;
    morseCode2 = code2;

    // 1 is added to keep the integrety of a double digit number
    // when be transferred to the button game
    if( morseCode1 > 2 ) {
      morseCode1 = morseCode1 % 2 + 1;
      morseCode1 = 2;
    }
    if( morseCode2 > 2 ) {
      morseCode2 = morseCode2 % 2 + 1;
      morseCode2 = 3;
    }
    
    // Determines which word will be displayed on the first LED
    // 1 - Pair
    // 2 - Pear
    // 3 - Pare
    switch( morseCode1 ) {
      case 1:
        break;
      case 2:
        for( int i = 0; i < 4; i++ ) {
          word1[i] = pear[i];
        }
        break;
      case 3:
        for( int i = 0; i < 4; i++ ) {
          word1[i] = pare[i];
        }
        break;
    }

    // Determines which word will be displayed on the second LED
    switch( morseCode2 ) {
      case 1:
        break;
      case 2:
        for( int i = 0; i < 4; i++ ) {
          word2[i] = pear[i];
        }
        break;
      case 3:
        for( int i = 0; i < 4; i++ ) {
          word2[i] = pare[i];
        }
        break;
    }
    
    //Convert words into morse code
    for( int i = 0; i < 4; i++ ) {
      morse1[i] = convertMorse( word1[i] );
      morse2[i] = convertMorse( word2[i] );
    }
}

/* Combines the two morse code words to be sent out
 * The first morse code is represented by the first digit
 * The second morse code is represented by the second digit
 */
uint8_t MorseCode::getMorse() {
  String morse1S = String (morseCode1);
  String morse2S = String (morseCode2);
  String combineMorseS = morse1S + morse2S;
  uint8_t combineMorseI = combineMorseS.toInt();
  return (uint8_t) combineMorseI;
}

/*Called every time the associated timer is changed
 *Updates a counter and if the counter is equal to
 *time units variable then the next state is determined*/
void MorseCode::receiveDataFromSubject( Subject *subj ) {
  static uint8_t word1Counter = 0;
  static uint8_t word2Counter = 0;
  word1Counter++;
  word2Counter++;
  if( word1Counter > timeUnits1 ) {
    nextState1();
    word1Counter = 0;
  }
  if( word2Counter > timeUnits2 ) {
    nextState2();
    word2Counter = 0;
  }
  
}

/*FOR REFERENCE
 * . 1 time unit
 * - 3 time units
 * space between words is 7 time units
 * space between letters is 3 time units
 */
/*Determine the next state for led 1*/
void MorseCode::nextState1() {
  static uint8_t letterIndex1 = 0;
  static uint8_t symbolIndex1 = 0; 
  static char* currentLetter1 = morse1[0];
  static char currentSymbol1 = currentLetter1[0];
  static char nextSymbol1 = currentSymbol1;
  switch( currentSymbol1 ) {
    
    case '#'://designated as space between words
      led->clearMorse1();
      timeUnits1 = 7;
      letterIndex1 = 0;
      symbolIndex1 = 0;
      currentLetter1 = morse1[0];
      nextSymbol1 = currentLetter1[ symbolIndex1];
      break;

    case '*'://designated as space between symbols
      led->clearMorse1();
      timeUnits1 = 1;
      symbolIndex1++;
      nextSymbol1 = currentLetter1[ symbolIndex1 ];
      break;

    case '^'://designated as space between letters
      led->clearMorse1();
      timeUnits1 = 3;
      symbolIndex1 = 0;
      letterIndex1++;
      currentLetter1 = morse1[letterIndex1];
      nextSymbol1 = currentLetter1[ symbolIndex1 ]; 
      break;

    case '.':
      led->setMorse1();
      timeUnits1 = 1;
      if( currentLetter1[symbolIndex1+1] == 0 && letterIndex1 == 3 ){
        nextSymbol1 = '#'; 
      } else if (  currentLetter1[symbolIndex1+1] == 0 ) {
        nextSymbol1 = '^';
      } else {
        nextSymbol1 = '*';
      }
      break;

    case '-':
      led->setMorse1();
      timeUnits1 = 3;
       if( currentLetter1[symbolIndex1+1] == 0 && letterIndex1 == 3 ){
        nextSymbol1 = '#'; 
      } else if ( currentLetter1[symbolIndex1+1] == 0 ) {
        nextSymbol1 = '^';
      } else {
        nextSymbol1 = '*';
      }
      break;
  }

  
  currentSymbol1 = nextSymbol1;

}

/*Determine the next state for led 1*/
void MorseCode::nextState2() {
  static uint8_t letterIndex2 = 0;
  static uint8_t symbolIndex2 = 0;
  static char* currentLetter2 = morse2[0];
  static char currentSymbol2 = currentLetter2[0];
  static char nextSymbol2 = currentSymbol2;
  switch( currentSymbol2 ) {

    case '#'://designated as space between words
      led->clearMorse2();
      timeUnits2 = 7;
      letterIndex2 = 0;
      symbolIndex2 = 0;
      currentLetter2 = morse2[0];
      nextSymbol2 = currentLetter2[ symbolIndex2];
      break;

    case '*'://designated as space between symbols
      led->clearMorse2();
      timeUnits2 = 1;
      symbolIndex2++;
      nextSymbol2 = currentLetter2[ symbolIndex2 ];
      break;

    case '^'://designated as space between letters
      led->clearMorse2();
      timeUnits2 = 3;
      symbolIndex2 = 0;
      letterIndex2++;
      currentLetter2 = morse2[letterIndex2];
      nextSymbol2 = currentLetter2[ symbolIndex2 ]; 
      break;

    case '.':
      led->setMorse2();
      timeUnits2 = 1;
      if( currentLetter2[symbolIndex2+1] == 0 && letterIndex2 == 3 ){
        nextSymbol2 = '#'; 
      } else if (  currentLetter2[symbolIndex2+1] == 0 ) {
        nextSymbol2 = '^';
      } else {
        nextSymbol2 = '*';
      }
      break;

    case '-':
      led->setMorse2();
      timeUnits2 = 3;
       if( currentLetter2[symbolIndex2+1] == 0 && letterIndex2 == 3 ){
        nextSymbol2 = '#'; 
      } else if ( currentLetter2[symbolIndex2+1] == 0 ) {
        nextSymbol2 = '^';
      } else {
        nextSymbol2 = '*';
      }
      break;
  }
  currentSymbol2 = nextSymbol2;
}

/*Convert input characters in morse
 *Will return a pointer to the morse generated*/
char* MorseCode::convertMorse( char morseChar ) {
  switch ( morseChar ) {
      case 'a': return ".-";
                break;
      case 'e': return ".";
                break;
      case 'i': return "..";
                break;
      case 'p': return ".--.";
                break;
      case 'r': return ".-.";
                break;          
    }
    return {};  
}
