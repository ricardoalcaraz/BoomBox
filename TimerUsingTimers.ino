// Sets up countdown timer
#include <TM1637Display.h>
#define CLK 23 //can be any digital pin
#define DIO 22 //can be any digital pin
TM1637Display display(CLK, DIO);

// Used to display "LOSE" when timer is done
uint8_t endDisplay[] = {0x38, 0x3F, 0x6D, 0x79};

// Used to keep track of countdown timer
IntervalTimer clockTimer;
// Used to display countdown timer
// This is initalized at 5 minutes. Change leading number for different minutes
int totalTimer = 500;


void setup() {
  // Initalizing countdown timer
  display.setBrightness( 7 );
  display.setColon( true );
  display.showNumberDec(500);
  clockTimer.begin( countdownTimer, 1000000 );
  delay( 100 );
}

void loop() {
}

// Used to display the countdown timer
void countdownTimer () {
  Serial.print( totalTimer );
    // End display when timer is done
  if ( totalTimer == 0 ) {
    display.setColon( false );
    display.setSegments(endDisplay);
    clockTimer.end();
  // Decrements minutes
  } else if ( ( totalTimer % 100 ) > 60 | totalTimer % 100 == 0 ) {
    // Used so when timer goes to 2:00 to 1:59 as opposed to 2:00 to 1:60
    totalTimer = totalTimer - 41;
    display.showNumberDec( totalTimer );
  // Decrements seconds 
  } else {
    totalTimer = totalTimer - 1;
    display.showNumberDec( totalTimer );
  }
}
  


