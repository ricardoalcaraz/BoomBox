#include <Bounce2.h>
#include "LED.h"
#include "Arduino.h"

// random RNG
#define PRREG(x) Serial.print(#x" 0x"); Serial.println(x,HEX)

#define REPS 50 //not needed in this variant
#define MYDLY 500 //loop delay in milliseconds

#define RNG_CR_GO_MASK                           0x1u
#define RNG_CR_HA_MASK                           0x2u
#define RNG_CR_INTM_MASK                         0x4u
#define RNG_CR_CLRI_MASK                         0x8u
#define RNG_CR_SLP_MASK                          0x10u
#define RNG_SR_OREG_LVL_MASK                     0xFF00u
#define RNG_SR_OREG_LVL_SHIFT                    8
#define RNG_SR_OREG_LVL(x)                       (((uint32_t)(((uint32_t)(x))<<RNG_SR_OREG_LVL_SHIFT))&RNG_SR_OREG_LVL_MASK)
#define SIM_SCGC6_RNGA    ((uint32_t)0x00000200)

SimonSays::SimonSays( uint8_t code, Timer *timer ) {
	codeWord = code;
}

void SimonSays::init() {
	SIM_SCGC6 |= SIM_SCGC6_RNGA; // enable RNG
    PRREG(SIM_SCGC6);
    RNG_CR &= ~RNG_CR_SLP_MASK;
    RNG_CR |= RNG_CR_HA_MASK;  // high assurance, not needed
    PRREG(RNG_CR);
    PRREG(RNG_SR);
	
	initializeLEDSequence();
	initializeButtonSequence( codeWord );
	initializeButtons();
	initializeLEDs();
}

bool SimonSays::isGameCompleted() {
	return gameWon;
} 

uint8_t SimonSays::numberErrors() {
	return errors;
}

void SimonSays::updateModule() {
	playSimonSays;
	displaySimonSays;
}

void SimonSays::terminate() {
	leds.setStatus( LEDoff );
	leds.update();	
}

void SimonSays::initializeLEDSequence() {
	
	Serial.begin(9600);
	Serial.println("Finished Setup");
	  
	// Empty space between sequences
	simonSaysSequence[0] = 0;
	simonSaysSequence[1] = 0;
	buttonSequence[0] = 0;
	buttonSequence[1] = 0;

	// Generates random sequence
	for( int x = 2; x < 10; x++ ) {
		simonSaysSequence[x] =  ( trng() % 4 ) + 1;
		// buttonSequence[x] = simonSaysSequence[x];
	}
}


void SimonSays::initializeButtonSequence( codeWord ) {
	if ( codeWord == 1 ) {
		for( int x = 2; x < 10; x++ ) {
		 switch ( simonSaysSequence[x]  ) {
		  case 1:
			buttonSequence[x] = 2;
			break;
		  case 2: 
			buttonSequence[x] = 1;
			break;
		  case 3: 
			buttonSequence[x] = 4;
			break;
		  case 4: 
			buttonSequence[x] = 3;
			break;
		  }  
		}
	} else if ( codeWord == 2 ) {
		for( int x = 2; x < 10; x++ ) {
		 switch ( simonSaysSequence[x]  ) {
		  case 1:
			buttonSequence[x] = 3;
			break;
		  case 2: 
			buttonSequence[x] = 4;
			break;
		  case 3: 
			buttonSequence[x] = 1;
			break;
		  case 4: 
			buttonSequence[x] = 2;
			break;
		  }  
		}
	} else if ( codeWord == 3 ) {
		for( int x = 2; x < 10; x++ ) {
		 switch ( simonSaysSequence[x]  ) {
		  case 1:
			buttonSequence[x] = 3;
			break;
		  case 2: 
			buttonSequence[x] = 1;
			break;
		  case 3: 
			buttonSequence[x] = 4;
			break;
		  case 4: 
			buttonSequence[x] = 2;
			break;
		  }  
		}  
	} else if ( code == 4 ) {
		for( int x = 2; x < 10; x++ ) {
		 switch ( simonSaysSequence[x]  ) {
		  case 1:
			buttonSequence[x] = 4;
			break;
		  case 2: 
			buttonSequence[x] = 3;
			break;
		  case 3: 
			buttonSequence[x] = 2;
			break;
		  case 4: 
			buttonSequence[x] = 1;
			break;
		  }  
		}   
	} else if ( codeWord == 5 ) {
		for( int x = 2; x < 10; x++ ) {
		 switch ( simonSaysSequence[x]  ) {
		  case 1:
			buttonSequence[x] = 1;
			break;
		  case 2: 
			buttonSequence[x] = 4;
			break;
		  case 3: 
			buttonSequence[x] = 3;
			break;
		  case 4: 
			buttonSequence[x] = 2;
			break;
		  }  
		} 
	} else if ( codeWord == 6 ) {
		for( int x = 2; x < 10; x++ ) {
		 switch ( simonSaysSequence[x]  ) {
		  case 1:
			buttonSequence[x] = 3;
			break;
		  case 2: 
			buttonSequence[x] = 2;
			break;
		  case 3: 
			buttonSequence[x] = 4;
			break;
		  case 4: 
			buttonSequence[x] = 1;
			break;
		  }  
		}   
	} else if ( code == 7 ) {
		for( int x = 2; x < 10; x++ ) {
		 switch ( simonSaysSequence[x]  ) {
		  case 1:
			buttonSequence[x] = 2;
			break;
		  case 2: 
			buttonSequence[x] = 4;
			break;
		  case 3: 
			buttonSequence[x] = 3;
			break;
		  case 4: 
			buttonSequence[x] = 1;
			break;
		  }  
		} 
	}
}

void SimonSays::initializeButtons() {
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
}

void SimonSays::initializeLEDs() {
	// Initalize LED
	leds.init();
	// Starts time every half a second
	simonSaysTimer.begin( displaySimonSays, 500000 );
}

void SimonSays::playSimonSays() {
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


		if ( buttonPressed == buttonSequence[ buttonRound ] ) {
			if ( buttonRound == simonSaysRound ) {
				buttonRound = 1;
				simonSaysRound ++;
			} else {
				buttonRound ++;
			}
		} else if ( buttonPressed != 0 ) {
			errors ++;
			simonSaysRound = 2;
			buttonRound = 2;
			currentSSDisplay = 0;
			leds.setStatus( B11111111 );
			leds.update();
		}
	}
}
void SimonSays::displaySimonSays(){
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

		if ( buttonRound != 2 && simonSaysRound != 2  ) {
			displayLED = LEDoff;
			currentSSDisplay = 2;
		}

		leds.setStatus( displayLED );
		leds.update();
	} else {
		gameWon = true;
		leds.setStatus( LEDoff );
		leds.update();
	}
}
