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
//Pin declarations
const uint8_t CLK_Pin = 23;
const uint8_t DIO_Pin = 22;

//Initialize needed objects
LED led;
CountdownTimer countdownClock;
ClockDisplay clockDisplay( CLK_Pin, DIO_Pin );
LCDDisplay wordScreen;
SimonSaysModule simonSays( &led );
ButtonGameModule buttonGame( &led );

uint8_t wordScreecnCode;

bool checkWin;

HalfSecondTimer halfSecClk;
MorseCode morse( &led );
//--------------------------------------------------

// WHAT DOES THIS DOO????
struct BoomBox_t {
  GameModule** games = new GameModule*[6];
  uint8_t size;
}; typedef struct BoomBox_t BoomBox;

BoomBox boomBox;

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

  //Start clock that updates observers every half second
  halfSecClk.start();
  //Attach any interested observers to half second clock
  morse.attachSubject( halfSecondClk.getSubject() );
  simonSays.attachSubject( halfSecondClk.getSubject() );
  buttonGame.attachSubject( countdownClock.getSubject() );
  
  //Initialize main game structure
  // WHAT DOES THIS DO
  boomBox.size = 2;
  boomBox.games[0] = &simonSays; // WHY AND
  boomBox.games[1] = &buttonGame;
  Serial.println("here");
  Serial.begin( 57600 );
}

void loop() {
  static uint8_t gameWon = 0;
  static uint8_t errors = 0;
  if ( countdownClock.getCurrentTime() == 0 ) {
    gameWon = 2;
  }
  switch ( gameWon ) {
    case 0: // Playing Game
      // Updates all module
      // Checks to see the number of errors made in each game
      // Checks to see if the user won any games
      checkWin = true; // Set true as default, will be set false if one game is not completed
      for( int i = 0; i < boomBox.size; i++ ) {
        boomBox.games[i]->updateModule(); // Update game modules such as display and user interaction
        errors = boomBox.games[i]->numberErrors() + errors; // Gets the number of errors

        // If one game has not been completed
        if ( boomBox.games[i] -> isGameCompleted() == false ) {
          checkWin = false;
        }
        // If  a user has made more than three errors they lose
        if ( errors < 4 ) {
          gameWon = 2;
        }
      }

      if ( checkWin == true ) {
        gameWon = 1;
      }
      break;
    case 1: // Won Game
      countdownClock.stopCountdown();
      break;
    case 2: // Lost Game
      countdownClock.stopCountdown();
      clockDisplay.displayLose();
      for( int i = 0; i < boomBox.size; i++ ) {
        boomBox.games[i]->terminate(); // Update game modules such as display and user interaction
      }
      break;
  }
  
  Serial.println( "Code Word: ");
  Serial.println( wordScreen.getCode() );
  led.update();
  delay(100);//Temporary delay to stop game from updating too rapidly
}


