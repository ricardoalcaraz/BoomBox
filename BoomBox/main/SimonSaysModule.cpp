
#include <Bounce2.h>
#include "LED.h"
#include "Arduino.h"
#include "SimonSaysModule.h"


SimonSaysModule::SimonSaysModule( uint8_t codeWord ) {
	this->code = codeWord;
}

void SimonSaysModule::init() {
	initializeLEDSequence();
	initializeButtonSequence( code );
	initializeButtons();
	initializeLEDs();
}

bool SimonSaysModule::isGameCompleted() {
	return gameWon;
} 

uint8_t SimonSaysModule::numberErrors() {
	return errors;
}

void SimonSaysModule::updateModule() {
	playSimonSays();
	displaySimonSays();
}

void SimonSaysModule::terminate() {
	leds.setStatus( LEDoff );
	leds.update();	
}

void SimonSaysModule::initializeLEDSequence() {
	
	Serial.begin(9600);
	Serial.println("Finished Setup");
	  
	// Empty space between sequences
	simonSaysSequence[0] = 0;
	simonSaysSequence[1] = 0;
	buttonSequence[0] = 0;
	buttonSequence[1] = 0;

	// Generates random sequence
	for( int x = 2; x < 10; x++ ) {
		simonSaysSequence[x] =  ( ranNum.trng() % 4 ) + 1;
		// buttonSequence[x] = simonSaysSequence[x];
	}
}


void SimonSaysModule::initializeButtonSequence( uint8_t code ) {
	if ( code == 1 ) {
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
	} else if ( code == 2 ) {
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
	} else if ( code == 3 ) {
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
	} else if ( code == 5 ) {
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
	} else if ( code == 6 ) {
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

void SimonSaysModule::initializeButtons() {
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

void SimonSaysModule::initializeLEDs() {
	// Initalize LED
	leds.init();
	// Starts time every half a second
	simonSaysTimer.begin( displaySimonSays, 500000 );
}

void SimonSaysModule::playSimonSays() {
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


void SimonSaysModule::displaySimonSays(){
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
		