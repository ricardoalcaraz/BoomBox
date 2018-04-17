#include "MorseCode.h"

const char pear[4] = {'p','e','a','r'};
const char pair[4] = {'p','a','i','r'};
const char pare[4] = {'p','a','r','e'};
//Constructor
MorseCode::MorseCode(uint8_t code, LED* led) {
  this->led = led;
  //Pick which words will be displayed on the LEDs
  switch( code ) {
    case 1:
      for( int i = 0; i < 4; i++ ) {
        word1[i] = pear[i];
        word2[i] = pair[i];
      }
      break;
    case 2:
      for( int i = 0; i < 4; i++ ) {
        word1[i] = pare[i];
        word2[i] = pear[i];
      }
      break;
  }
  
  //Convert words into morse code
  for( int i = 0; i < 4; i++ ) {
    morse1[i] = convertMorse( word1[i] );
    morse2[i] = convertMorse( word2[i] );
  }

}

/*
 * . 1 time unit
 * - 3 time units
 * space between words is 7 time units
 * space between letters is 3 time units
 */
void MorseCode::receiveDataFromSubject( Subject *subj ) {
  static uint8_t word1Counter = 0;
  static uint8_t word2Counter = 0;
  word1Counter++;
  word2Counter++;
  if( word1Counter > timeUnits1 ) {
    nextState();
    word1Counter = 0;
    word2Counter = 0;
  }
  
}

void MorseCode::nextState() {
  static uint8_t letterIndex1 = 0;
  static uint8_t letterIndex2 = 0;
  static uint8_t symbolIndex1 = 0; 
  static uint8_t symbolIndex2 = 0;
  static char* currentLetter1 = morse1[0];
  static char* currentLetter2 = morse2[0];
  static uint8_t symbolSize1 = sizeof(morse1[0]);
  static uint8_t symbolSize2 = sizeof(morse2[1]);
  static char currentSymbol1 = currentLetter1[0];
  static char nextSymbol1 = currentSymbol1;
  static char currentSymbol2 = currentLetter2[0];
  static char nextSymbol2 = currentSymbol2;
  

  switch( currentSymbol1 ) {
    
    case '#'://designated as space between words
      led->clearMorse1();
      timeUnits1 = 7;
      letterIndex1 = 0;
      symbolIndex1 = 0;
      currentLetter1 = morse1[0];
      symbolSize1 = sizeof( currentLetter1 );
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
      symbolSize1 = sizeof( currentLetter1 );
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

  switch( currentSymbol2 ) {

    case '#'://designated as space between words
      led->clearMorse2();
      timeUnits2 = 7;
      letterIndex2 = 0;
      symbolIndex2 = 0;
      currentLetter2 = morse2[0];
      symbolSize2 = sizeof( currentLetter2 );
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
      symbolSize2 = sizeof( currentLetter2 );
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
  currentSymbol1 = nextSymbol1;
  currentSymbol2 = nextSymbol2;

}

char* MorseCode::convertMorse( char morseChar ) {
  char* morse;
  switch ( morseChar ) {
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
