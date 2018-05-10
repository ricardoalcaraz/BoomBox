#include "CutWireGameModule.h"

CutWireGameModule::CutWireGameModule( LED* led ) {
  this->leds=led;
}

/*Initialize pins used and configure first LED
 * sequence.*/
void CutWireGameModule::init( uint8_t code ) {
  this->code = code;
  initializeFirstSequence( code );
  //8 pins from 1-9 are used
  for( int i = 1; i < 10; i+=2 ) {
    pinMode(i, OUTPUT);
    digitalWrite(i , HIGH);
  }
  for( int i = 2; i < 10; i+=2 ) {
    pinMode(i,INPUT);
  }

}

//Simplified solutions to the stages
const uint8_t stage1Solution = B10110010;
const uint8_t stage2Solution = B10001010;
const uint8_t stage3Solution = B01000101;

/*Check the state that the wires are in and
 *determine whether the user has successfully
 *completed a sequence*/
void CutWireGameModule::updateModule() {
  uint8_t playerState = 0;
  for( int i = 1; i < 9; i++ ) {
    currentState |= _BV( digitalRead(i) );
  }
  if( currentState == 1 && playerState = stage1Solution) {
    currentState++;
    initializeSecondSequence();
  } else if( currentState == 2 && playerState = stage2Solution ) {
    currentState++;
  } else if( currentState == 2 && playerState = stage3Solution ) {
    terminate();
    gameWon=true;
  }
}

//Return number of errors
uint8_t CutWireGameModule::numberErrors() {
  return errors;
}

//Return whether the game was one
bool CutWireGameModule::isGameCompleted() {
  return gameWon;
}


//Initialize leds for first sequence
const uint8_t stage1LedSequence1 = B1010000;
const uint8_t stage1LedSequence1 = B1101011;
void CutWireGameModule::initializeFirstSequence() {
  leds->setByte2( stage1LedSequence1 );
  leds->setByte3( stage1LedSequence2 );
}

//Initialize leds for seconds sequence
const uint8_t stage2LedSequence1 = B11110000;
const uint8_t stage2LedSequence2 = B00001111;
void CutWireGameModule::initializeSecondSequence() {
  leds->setByte2( stage2LedSequence1 );
  leds->setByte3( stage2LedSequence2 );
}

//Initialize leds for third sequence
const uint8_t stage3LedSequence1 = B11101011;
const uint8_t stage3LedSequence2 = B10111111;
void CutWireGameModule::initializeFinalSequence() {
  leds.setByte2( stage3LedSequence1 );
  leds.setByte3( stage3LedSequence2 );
}
