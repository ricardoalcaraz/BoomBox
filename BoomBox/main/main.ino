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

// WHAT DOES THIS DOO????
struct BoomBox_t {
  GameModule** games = new GameModule*[6];
  uint8_t size;
}; typedef struct BoomBox_t BoomBox;

BoomBox boomBox;

void setup() {

  //Initialize the leds
  led.init();
  //Initialize wordscreen
  wordScreen.init( trng() );

  //Initialize Simon Says
  simonSays.init( wordScreen.getCode() );

  //Create clock that countdown every second
  countdownClock.startCountdown( 360 );
  //Update any observers that may need this info
  clockDisplay.attachSubject( countdownClock.getSubject() );

  rngsetup(); //temporary will be replaced with random object later

  //Start clock that updates observers every half second
  halfSecClk.start();
  //Attach any interested observers to half second clock
  morse.attachSubject( halfSecondClk.getSubject() );
  simonSays.attachSubject( halfSecondClk.getSubject() );
  
  //Initialize main game structure
  // WHAT DOES THIS DO
  boomBox.size = 1;
  boomBox.games[0] = &simonSays; // WHY AND
  Serial.begin( 57600 );
}

void loop() {
  for( int i = 0; i < boomBox.size; i++ ) {
  	boomBox.games[i]->updateModule();
  }
  led.update();
  delay(100);//Temporary delay to stop game from updating too rapidly
}


