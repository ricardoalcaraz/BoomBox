//Only the header file should be include in the cpp
#include "ButtonGameModule.h"


ButtonGameModule::ButtonGameModule( LED* led ) {
	this->leds = led;
}

/*Initalize modules*/
void ButtonGameModule::init( uint8_t code ) {
	// put your setup code here, to run once:
	// Initalize button
	pinMode( buttonPin, INPUT_PULLUP );
	pressButton.attach( buttonPin );
	pressButton.interval( 5 );

	// Convert double digit code word to determine the two morse code words
	convertMorseCode( code );
}



/*Returns if the game was completed
*/
bool ButtonGameModule::isGameCompleted() {
	return gameWon;
} 

/*Returns the number of errors for this specific game
*/
uint8_t ButtonGameModule::numberErrors() {
	return errors;
}

void ButtonGameModule::terminate() {
	leds->setStatus( offLED );
	leds->update();
  
}

/*Play the Button Game
*/
void ButtonGameModule::updateModule() {
	// put your main code here, to run repeatedly:
	// Enters when game is not finished
	if ( gameWon == false ) {
	// Generates random LED to display
	static uint8_t ranLED = ranNum.trng() % 4;
	// If the button is pressed
		if ( pressButton.fell() ) {
			// Displays the random LED
			switch( ranLED ) {
				case 0:
					displayLED = blueLED;
					break;
				case 1:
					displayLED = redLED;
					break;
				case 2:
					displayLED = greenLED;
					break;
				case 3:
					displayLED = offLED;
					break;
			}
			leds->setButtonGameLEDS( displayLED );
		// If the button is released
		} else if ( pressButton.rose() ) {
			convertTimer();
			if ( morse1 == morse2 ) { 
				wordsSame( ranLED );
			} else {
				wordsDifferent( ranLED );
			}
			leds->setButtonGameLEDS( offLED ); // Turns it off when LED is off
			// Checks to see if button was released on the correct display
			for ( int x = 0; x < 3; x++ ) {
				if ( timerDisplay[x] == correctNumRelease ) {
					gameWon = true; 
					break;
				} 
			}

			// Adds an error when incorrect release and generates another number
			if ( gameWon == false ) {
				ranLED = ranNum.trng() % 4;
				errors++;
			}
		  
		} 
		leds->update();
		pressButton.update();

	} else {
		leds->setButtonGameLEDS( offLED );
		leds->update();
	}
	
}


/** Determines the two morse code words from a double digit
 * First digit represents the fisrt morse code word
 * Second digit represents the second morse code word
 * 1 - pair
 * 2 - pear 
 * 3 - pare
 */
void ButtonGameModule::convertMorseCode( uint8_t codeToConvert ) {
	String codeS = ( String ) codeToConvert;
	morse1 = codeS.charAt(0) - '0';
	morse2 = codeS.charAt(1) - '0';
}

/**
 * Separates the three or two digit number being displayed on the timer 
 * into single digits that are then placed into the array.
 * This array will be used to make to check if the user released the
 * button on the correct number
 */
void ButtonGameModule::convertTimer() {
  int minutes = timerInt/60;
  int seconds = timerInt%60;
  String timer = ( String ) seconds;
  // Less than three digits on the timer
  if ( timerInt < 10 ) {
    timerDisplay[0] = timerInt;
    timerDisplay[1] = 0;
    timerDisplay[2] = 0;
  // More than three digits on the timer
  } else if ( timerInt < 60 ) {
    timerDisplay[0] = timer.charAt(0) - '0';
    timerDisplay[1] = timer.charAt(1) - '0';
    timerDisplay[2] = 0;
  } else {
    timerDisplay[0] = minutes;
    timerDisplay[1] = timer.charAt(0) - '0';
    timerDisplay[2] = timer.charAt(1) - '0';
  }
}

void ButtonGameModule::wordsSame( uint8_t ranLED ) {
	switch ( morse1 ) {
		case 1: // Pair
			switch( ranLED ) {
				case 0: // Pair - Blue
					correctNumRelease = 1;
					break;
				case 1: // Pair - Red
					correctNumRelease = 2;
					break;
				case 2: // Pair - Green
					correctNumRelease = 9;
					break;
				case 3: // Pair - None
					correctNumRelease = 8;
					break;
			}
			break;
		case 2: // Pare
			switch( ranLED ) {
				case 0: // Pair - Blue
					correctNumRelease = 6;
					break;
				case 1: // Pair - Red
					correctNumRelease = 5;
					break;
				case 2: // Pair - Green
					correctNumRelease = 3;
					break;
				case 3: // Pair - None
					correctNumRelease = 4;
					break;
			}		
			break;
		case 3: // Pear
			switch( ranLED ) {
				case 0: // Pair - Blue
					correctNumRelease = 7;
					break;
				case 1: // Pair - Red
					correctNumRelease = 5;
					break;
				case 2: // Pair - Green
					correctNumRelease = 6;
					break;
				case 3: // Pair - None
					correctNumRelease = 8;
					break;
			}
			break;
	}
}

void ButtonGameModule::wordsDifferent( uint8_t ranLED ) {
	if ( ( morse1 == 1 && morse1 == 3 ) || ( morse2 == 2 )  ) {
		switch( ranLED ) { // Pair, Pare OR Pear, Pare
			case 0: //  Blue
				correctNumRelease = 6;
				break;
			case 1: // Red
				correctNumRelease = 3;
				break;
			case 2: // Green
				correctNumRelease = 2;
				break;
			case 3: // None
				correctNumRelease = 4;
				break;
		}
	} else if ( ( morse1 == 1 && morse1 == 2 ) || ( morse2 == 3 ) ) { // Pair, Pear OR Pare, Pear
		switch( ranLED ) {
			case 0: // Blue
				correctNumRelease = 7;
				break;
			case 1: // Red
				correctNumRelease = 9;
				break;
			case 2: // Green
				correctNumRelease = 5;
				break;
			case 3: // None
				correctNumRelease = 1;
			break;
		}
	} else { // Pare, Pair OR Pear, Pair
		switch( ranLED ) {
			case 0: // Blue
				correctNumRelease = 7;
				break;
			case 1: // Red
				correctNumRelease = 8;
				break;
			case 2: // Green
				correctNumRelease = 2;
				break;
			case 3: // None
				correctNumRelease = 9;
				break;
		}
	}
}


void ButtonGameModule::receiveDataFromSubject( Subject *subj ) {
	// SET TIMERINT HERE??
  timerInt = subj->getVal();
  //Serial.println(timerInt);
}
