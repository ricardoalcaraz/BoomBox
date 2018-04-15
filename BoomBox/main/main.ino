#include "LED.h"
#include "ScoreKeeper.h"
#include "ClockDisplay.h"
#include "CountdownTimer.h"
#include "LCDDisplay.h"

//Pin declarations
const uint8_t CLK_Pin = 23;
const uint8_t DIO_Pin = 22;

//Initialize needed objects
CountdownTimer clock1;
ClockDisplay clockDisplay( CLK_Pin, DIO_Pin );
LED leds;
LCDDisplay wordScreen;

/*--------------------------------------------------*/
//-------------------------Initializers-------------------------
/*
We need an interrupt timer for our morse code so we can provide exact timings
needed in a morse code message. We will be using the built in teensy interrupt
objects to accomplish this
*/
const uint8_t morseLED1 = 29;
const uint8_t morseLED2 = 30;
const uint32_t timeUnit = 750000; //Value is in microseconds
IntervalTimer morseTimer;
char morseWord1[] = {'p','e','a','r'}; 
char morseWord2[] = {'p','a','i','r'};
char* morse1[4];
char* morse2[4];
bool stateChanged = false;
uint8_t currentTimeUnits = 0;


//--------------------------------------------------


void setup() {
  clockDisplay.attachSubject( clock1.getSubject() );
  clock1.startCountdown( 360 );
  rngsetup();
  wordScreen.init( trng() );
  
}

void loop() {

}



