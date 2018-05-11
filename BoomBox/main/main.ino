#include "LED.h"
#include "ScoreKeeper.h"
#include "ClockDisplay.h"
#include "CountdownTimer.h"
#include "LCDDisplay.h"
#include "SimonSaysModule.h"
#include "HalfSecondTimer.h"
#include "MorseCode.h"
#include "SimonSaysModule.h"
#include "ButtonGameModule.h"
#include "ObserverTester.h"
//Pin declarations
const uint8_t CLK_Pin = 23;
const uint8_t DIO_Pin = 22;

const uint8_t wireStatusLED = B10000000;
const uint8_t simonSaysStatusLED = B01000000;
//Initialize needed objects
LED led;
CountdownTimer countdownClock;
ClockDisplay clockDisplay( CLK_Pin, DIO_Pin );
LCDDisplay wordScreen;
SimonSaysModule simonSays( &led );
ButtonGameModule buttonGame( &led );
ScoreKeeper score( 3, 4 );

uint8_t wordScreenCode;

bool checkWin;

HalfSecondTimer halfSecClk;
MorseCode morse( &led );
//--------------------------------------------------

struct BoomBox_t {
  GameModule** games = new GameModule*[6];
  uint8_t size;
}; typedef struct BoomBox_t BoomBox;

BoomBox boomBox;

ObserverTester observerTester;

void setup() {

  // Initialize morse code
  morse.init( trng(), trng() );
  //Initialize the leds
  led.init();
  //Initialize wordscreen
  wordScreen.init( trng() );
  
  // Initalize the Button Game
  buttonGame.init( morse.getMorse() );

  //Initialize Simon Says
  simonSays.init( wordScreen.getCode() );
  
  //Create clock that countdown every second
  countdownClock.startCountdown( 360 );
  //Update any observers that may need this info
  clockDisplay.attachSubject( countdownClock.getSubject() );

  rngsetup(); //temporary will be replaced with random object later
  
  bool gameWon=false;

  //Start clock that updates observers every half second
  halfSecClk.start();
  //Attach any interested observers to half second clock
  morse.attachSubject( halfSecondClk.getSubject() );
  simonSays.attachSubject( halfSecondClk.getSubject() );
  buttonGame.attachSubject( countdownClock.getSubject() );
  
  //Initialize main game structure
  boomBox.size = 2;
  boomBox.games[0] = &simonSays;
  boomBox.games[1] = &buttonGame;
 // boomBox.games[2] = &cutWiresGame;
  Serial.println("Starting Game");
  Serial.begin( 57600 );
}

//Main loop
void loop() {
  //Check if observers can register and receive data from subject check serial output to see if it works
  observerTester.attachSubject( countdownClock.getSubject() );
  delay(2200);
  //unregister observers serial output should only have previous two entries
  countdownClock.getSubject()->unregisterObserver( 0 );
  delay(2000);
  //Check if observer can register with half second clock
  observerTester.attachSubject( halfSecondClk.getSubject() );
  delay(2200);
  //4 outputs should appear and they should be one
  halfSecondClk.getSubject()->unregisterObserver( 0 );
  delay(2000);

  //Nothing should appear

  //Visual check for all leds
  Serial.println("ALL Leds will blink twice then stay off, check for correct behavior");
  led.setAllLEDS();
  delay(1000);
  led.clearAllLEDS();
  delay(1000);
  led.setAllLEDS();
}


