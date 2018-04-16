#include "LED.h"
#include "ScoreKeeper.h"
#include "ClockDisplay.h"
#include "CountdownTimer.h"
#include "LCDDisplay.h"
#include "SimonSaysModule.h"
//Pin declarations
const uint8_t CLK_Pin = 23;
const uint8_t DIO_Pin = 22;

//Initialize needed objects
CountdownTimer clock1;
ClockDisplay clockDisplay( CLK_Pin, DIO_Pin );
LED leds;
LCDDisplay wordScreen;

uint8_t code = wordScreen.getCode();


//--------------------------------------------------


void setup() {
  clockDisplay.attachSubject( clock1.getSubject() );
  clock1.startCountdown( 360 );
  rngsetup(); 
  wordScreen.init( trng() );
  
}

void loop() {

}



