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


  //Initialize the leds
  led.init();
  //Initialize wordscreen
  wordScreen.init( 1 );
  
  // Initalize the Button Game
  buttonGame.init( morse.getMorse() );


  //Update any observers that may need this info
  clockDisplay.attachSubject( countdownClock.getSubject() );
  //Create clock that countdown every second
  
  one_sec_timer_init();
  
  
  bool gameWon=false;

  
  //Start clock that updates observers every half second
//  halfSecClk.start();
//  //Attach any interested observers to half second clock

//  simonSays.attachSubject( halfSecondClk.getSubject() );
//  buttonGame.attachSubject( countdownClock.getSubject() );
  
//  //Initialize main game structure
//  boomBox.size = 2;
//  boomBox.games[0] = &simonSays;
//  boomBox.games[1] = &buttonGame;
// // boomBox.games[2] = &cutWiresGame;
//  Serial.println("Starting Game");
  countdownClock.startCountdown( 360 );
  Serial.begin( 57600 );
}

//Main loop
void loop() {
  Serial.println( countdownClock.getCurrentTime() );
  if ( countdownClock.getCurrentTime() % 3 == 0 ) {
    countdownClock.resetCountdown();
    
    
  }
  delay(1000);

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

  static ScoreKeeper testScore( 3, 3 );
  if(testScore.isGameWon() == false){
    Serial.println("Scorekeeper game completed works");
  } else {
    Serial.println("ScoreKeeper game completed function does not work");
  }
  testScore.numErrors( 2 );

  if(testScore.getErrorsMade() == 2 ) {
    Serial.println("ScoreKeeper score counter works!");
  } else {
    Serial.println("ScoreKeeper score counter does not work :(");
  }

  testScore.gameCompleted();
  testScore.gameCompleted();
  testScore.gameCompleted();
  if(testScore.isGameWon()==true){
    Serial.println("Score keeper game tracker works");
  } else {
    Serial.println("Score keeper game tracker does not work");
  }

  //Testing the morse code
  Serial.println("Testing morse code. View attached LEDs and make sure they're blinking properly");
  morse.attachSubject( halfSecondClk.getSubject() );

  //Cut Wire Game Testing
//  Static CutWireGameModule wireGame;
//  Serial.println("Make sure wires are attached from pins 1-8");
//  wireGame.init(1);
//  Serial.println("Please attach wires from pin 1 to pin 5 and from pin 2 to 8 and from 3 to 7");
//  delay(2000);
//  if(wireGame.getCurrentStage==2){
//    Serial.println("Stage 1 solved correctly");
//  } else{
//    Serial.println("Stage solved incorrectly or does not work, double check connections and reset");
//  }
//  Serial.println("Please attach wires from pin 2 to pin 5 and from pin 2 to 8 and from 4 to 5");
//  delay(2000);
//  if(wireGame.getCurrentStage==3){
//    Serial.println("Stage 2 solved correctly");
//  }else{
//    Serial.println("Stage solved incorrectly or does not work, double check connections and reset");
//  }
//  Serial.println("Please attach wires from pin 1 to pin 3 and from pin 2 to 4 and from 6 to 8");
//  delay(2000);
//  if(wireGame.getCurrentStage==4){
//    Serial.println("Stage 3 solved correctly");
//  }else{
//    Serial.println("Stage solved incorrectly or does not work, double check connections and reset");
//  }

//  Serial.println("Please attach buttons to pins 1-4 and leds to pins 5-8");
//  Serial.println("Follow the sequence of leds");
//    //Initialize Simon Says
//  simonSays.init( 1 );
//  while( !simonSays.isGameCompleted() ){
//    
//  }
  
}

void one_sec_timer_init() {
    TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  OCR1B = 31248;
  // turn on CTC mode
  
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  TIMSK1 |= (1 << OCIE1B);
}


ISR(TIMER1_COMPA_vect){
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  countdownClock.countdown();

}

ISR(TIMER_COMPB_vect){
  halfSecClk.tick();
}

