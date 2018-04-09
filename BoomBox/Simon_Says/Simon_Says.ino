#include <Bounce2.h>
#include "LED.h"

// Used to display LEDS
LED leds;

// Pins for buttons
const uint8_t blueButton = 36;
const uint8_t redButton = 35;
const uint8_t greenButton = 34;
const uint8_t purpleButton = 33;

// Boolean specific LED
const int8_t blueLED = B00001000;
const int8_t redLED = B00010000;
const int8_t greenLED = B00100000;
const int8_t purpleLED = B11000000;

// All LEDS off
const int8_t LEDoff = B00000000;

uint32_t simonSaysSequence[ 10 ];

// Current position in Simon Says Sequence
uint8_t simonSaysRound = 2;
uint8_t nextState = LOW; 
// Starts at zero for space between sequence
uint8_t currentSSDisplay = 0;

// Used so it only recognizes button pressed once
Bounce blue = Bounce();
Bounce red = Bounce();
Bounce green = Bounce();
Bounce purple = Bounce();


// Used to display sequence
IntervalTimer simonSaysTimer;

// Errors
uint8_t errors = 0;

// Game Won
bool gameWon = false;

void setup() {
  // Initalize LED
  leds.init();

  // Initalize buttons
  pinMode( blueButton, INPUT_PULLUP );
  pinMode( redButton, INPUT_PULLUP );
  pinMode( greenButton, INPUT_PULLUP );
  pinMode( purpleButton, INPUT_PULLUP );
  blue.attach( blueButton );
  blue.interval( 5 );
  
  red.attach( redButton );
  red.interval( 5 );

  green.attach( greenButton );
  green.interval( 5 );

  purple.attach( purpleButton );
  purple.interval( 5 );
 
 

  // Random number generator
  rngsetup();
  Serial.begin(9600);
  Serial.println("Finished Setup");
  // Empty space between sequences
  simonSaysSequence[0] = 0;
  simonSaysSequence[1] = 0;

  // Generates random sequence
  for( int x = 2; x < 10; x++ ) {
    simonSaysSequence[x] =  ( trng() % 4 ) + 1;
    Serial.print(simonSaysSequence[x]);
    Serial.print(" ");
  }
  Serial.println();

  // Starts time every half a second
  simonSaysTimer.begin( displaySimonSays, 500000 );
}

void loop() {
  // put your main code here, to run repeatedly:
  playSimonSays();
  Serial.print( "Simon says round: " );
  Serial.println( simonSaysRound);
  Serial.print( "Current ss display ");
  Serial.println( currentSSDisplay );
  

    
  delay(50);
}

void playSimonSays() {
  static uint8_t currentRound = 2;
  static uint8_t buttonPressed = 0;
  
  blue.update();
  red.update(); 
  green.update();
  purple.update();
  if ( simonSaysRound != 10 ) { 
    
    if ( blue.fell() ) {
      buttonPressed = 1;
    } else if ( red.fell() ) {
      buttonPressed = 2;
    } else if ( green.fell() ) {
      buttonPressed = 3;
    } else if ( purple.fell() ) {
      buttonPressed = 4;
    } else {
      buttonPressed = 0;
    }


    if ( buttonPressed == simonSaysSequence[ currentRound ] ) {
      Serial.println( " CORRECT " );
      if ( currentRound == simonSaysRound ) {
        currentRound = 1;
        simonSaysRound ++;
      } else {
        currentRound ++;
      }
    } else if ( buttonPressed != 0 ) {
      Serial.println( " WRONG " );
      errors ++;
      simonSaysRound = 2;
      currentRound = 2;
      currentSSDisplay = 0;
      leds.setStatus( B11111111 );
      leds.update();
    }
  }
}

bool isGameCompleted () {
  return gameWon; 
}

int numberErrors () {
  return errors;
}

void displaySimonSays() {
  if ( simonSaysRound != 10 ) { 
    // What LED is displayed 
    static uint8_t displayLED = B00000000;
    switch ( simonSaysSequence[currentSSDisplay] ) {
      case 0: 
        displayLED = LEDoff;
        break;
      case 1:
        displayLED = blueLED;
        break;
      case 2: 
        displayLED = redLED;
        break;
      case 3: 
        displayLED = greenLED;
        break;
      case 4: 
        displayLED = purpleLED;
        break;
    }
    
    // Toggles between on and off
    if ( nextState == HIGH ) {
      nextState = LOW;
      displayLED = LEDoff;
    } else {
      nextState = HIGH;
      // Restarts sequence
      if ( currentSSDisplay == simonSaysRound ) {
        currentSSDisplay = 0;
      } else {
        currentSSDisplay ++;
      }  
    }
    
    leds.setStatus( displayLED );
    leds.update();
  } else {
    gameWon = true;
    leds.setStatus( LEDoff );
    leds.update();
  }
  
}



