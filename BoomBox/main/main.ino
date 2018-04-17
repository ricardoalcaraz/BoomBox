#include "LED.h"
#include "ScoreKeeper.h"
#include "ClockDisplay.h"
#include "CountdownTimer.h"
#include "LCDDisplay.h"
#include "SimonSaysModule.h"
#include "HalfSecondTimer.h"
#include "MorseCode.h"
#include "SimonSaysModule.h"
//Pin declarations
const uint8_t CLK_Pin = 23;
const uint8_t DIO_Pin = 22;

//Initialize needed objects
LED led;
CountdownTimer countdownClock;
ClockDisplay clockDisplay( CLK_Pin, DIO_Pin );
LCDDisplay wordScreen;
SimonSaysModule simonSays( &led );

uint8_t wordScreenCode;

HalfSecondTimer halfSecClk;
MorseCode morse( 1, &led );
//--------------------------------------------------


void setup() {
  led.init();
  clockDisplay.attachSubject( countdownClock.getSubject() );
  countdownClock.startCountdown( 360 );
  rngsetup(); 
  halfSecClk.start();
  morse.attachSubject( halfSecondClk.getSubject() );
  wordScreen.init( trng() );
  wordScreenCode = wordScreen.getCode();
  Serial.begin( 57600 );
}

void loop() {
  led.update();
  delay(100);
}


