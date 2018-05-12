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
const uint8_t CLK_Pin = A3;
const uint8_t DIO_Pin = A2;

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
  morse.init( random(100), random(100) );
  //Initialize the leds
  led.init();
  //Initialize wordscreen
  wordScreen.init( 1 );
  
  // Initalize the Button Game
  buttonGame.init( morse.getMorse() );

  //Initialize Simon Says
  simonSays.init( wordScreen.getCode() );
  //Update any observers that may need this info
  clockDisplay.attachSubject( countdownClock.getSubject() );
  //Create clock that countdown every second
  countdownClock.startCountdown( 360 );
  one_sec_timer_init();
  
  
  bool gameWon=false;

  
  //Start clock that updates observers every half second
//  halfSecClk.start();
//  //Attach any interested observers to half second clock
//  morse.attachSubject( halfSecondClk.getSubject() );
//  simonSays.attachSubject( halfSecondClk.getSubject() );
//  buttonGame.attachSubject( countdownClock.getSubject() );
  
//  //Initialize main game structure
//  boomBox.size = 2;
//  boomBox.games[0] = &simonSays;
//  boomBox.games[1] = &buttonGame;
// // boomBox.games[2] = &cutWiresGame;
//  Serial.println("Starting Game");
  Serial.begin( 57600 );
}

//Main loop
void loop() {
  delay(100);
}

void one_sec_timer_init() {
    TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

