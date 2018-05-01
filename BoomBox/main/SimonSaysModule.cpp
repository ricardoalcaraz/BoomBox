//Only the header file should be include in the cpp
#include "SimonSaysModule.h"


SimonSaysModule::SimonSaysModule( LED* led ) {
	this->leds = led;
}

/*Initalize modules*/
void SimonSaysModule::init(uint8_t code) {
	this->code = code;
	initializeLEDSequence();
	initializeButtonSequence( code );
	initializeButtons();
}

bool SimonSaysModule::isGameCompleted() {
	return gameWon;
} 

uint8_t SimonSaysModule::numberErrors() {
	return errors;
}

void SimonSaysModule::updateModule() {
	playSimonSays();
}

void SimonSaysModule::terminate() {
	leds->setStatus( LEDoff );
  
}

void SimonSaysModule::initializeLEDSequence() {
	// Empty space between sequences
	simonSaysSequence[0] = 0;
	simonSaysSequence[1] = 0;
	buttonSequence[0] = 0;
	buttonSequence[1] = 0;

	// Generates random sequence
	for( int x = 2; x < 10; x++ ) {
		simonSaysSequence[x] =  ( ranNum.trng() % 4 ) + 1;
    Serial.print(simonSaysSequence[x]);
    Serial.print(" ");
		// buttonSequence[x] = simonSaysSequence[x];
	}
  Serial.println("");
}


void SimonSaysModule::initializeButtonSequence( uint8_t code ) {

  for( int x = 2; x < 10; x++ ) {
       switch ( simonSaysSequence[x]  ) {
        case 1:
        buttonSequence[x] = 1;
        break;
        case 2: 
        buttonSequence[x] = 2;
        break;
        case 3: 
        buttonSequence[x] = 3;
        break;
        case 4: 
        buttonSequence[x] = 4;
        break;
      }  
  }
//  Determines how the buttons should be pressed based on code
  // Fantasia
	if ( code == 0 ) {
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
  // diabolique
	} else if ( code == 1 ) {
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
  // diabolic
	} else if ( code == 2 ) {
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
  // none
	} else if ( code == 3 ) {
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
  // stop 
	} else if ( code == 4 ) {
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
  // euripides
	} else if ( code == 5 ) {
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
  // "blank"
	} else if ( code == 6 ) {
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
  // Ensures that it only recognizes that button is only pressed once
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


void SimonSaysModule::playSimonSays() {
  
	static uint8_t buttonPressed = 0;

  // Needed to check if button was pressed
	blue.update();
	red.update(); 
	green.update();
	purple.update();
  
	if ( simonSaysRound != 10 ) { 
    // If simon says game is not on the last round
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
   
    Serial.print("PRESS: ");
    Serial.println( buttonSequence[ buttonRound ] ); 

    
    // Checks to see if the button pressed is correct
		if ( buttonPressed == buttonSequence[ buttonRound ] ) {
      // Once user presses the last button in sequence
      // Resets buttonRound in order for the user to press the next
      // sequence of buttons starting from the beginning
			if ( buttonRound == simonSaysRound ) {
				buttonRound = 1;
				simonSaysRound ++;
      // Adds in order to check the next button that should be pressed
			} else {
				buttonRound ++;
			}
    // If wrong button is pressed adds an error and starts game from the beginning
		} else if ( buttonPressed != 0 ) {
			errors ++;
			simonSaysRound = 2;
			buttonRound = 2;
			currentSSDisplay = 0;
			leds->setStatus( B11111111 );
		}
	}
}


// Boolean specific LED
const int8_t blueLED = B10000000;
const int8_t redLED = B01000000;
const int8_t greenLED = B00100000;
const int8_t purpleLED = B00011000;
    
void SimonSaysModule::displaySimonSays( ){
  static uint8_t displayLED = B00000000;
  static uint8_t nextState = LOW;

	if ( simonSaysRound != 10 ) { 
    // If the game is not over
    Serial.println( simonSaysSequence[currentSSDisplay] );
		switch ( simonSaysSequence[currentSSDisplay] ) {
      // Used for period between displayed sequences
			case 0: 
        Serial.println("DISPLAY: OFF");
				displayLED = LEDoff;
				break;
			case 1:
        Serial.println("DISPLAY: BLUE");
				displayLED = blueLED;
				break;
			case 2: 
        Serial.println("DISPLAY: RED");
				displayLED = redLED;
				break;
			case 3: 
        Serial.println("DISPLAY: GREEN");
				displayLED = greenLED;
				break;
			case 4: 
        Serial.println("DISPLAY: PURPLE");
				displayLED = purpleLED;
				break;
		}

		// Toggles between on and off in order to blink LEDs
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

    // Stops display LEDs when user is trying to guess the sequence
		if ( buttonRound != 2 && simonSaysRound != 2  ) {
			displayLED = LEDoff;
			currentSSDisplay = 2;
		}

   Serial.print("CURRENT DISPLAY: ");
   Serial.println(displayLED);
		leds->setStatus( displayLED );
	} else {
		gameWon = true;
		leds->setStatus( LEDoff );
	}
    
}
		
void SimonSaysModule::receiveDataFromSubject( Subject *subj ) {
	displaySimonSays();
}
