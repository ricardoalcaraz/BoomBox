#ifndef SimonSaysModule_h
#define SimonSaysModule_h
//Any libraries should go in the same folder and referenced with quotation marks
//so we can all have the same behavior and not have to install libraries
#include "Bounce2.h"
#include "LED.h"
#include "RandomNumber.h"
#include "GameModule.h"
#include "Observer.h"
#include "Arduino.h"

// Name: Simon Says Game
// Author: Kristen Oduca
// Version: 1.0
// Notes: Game module for Simon Says. User must repeat displayed sequence	
//
//
//Inherits from Game Module class and Observer class
class SimonSaysModule : public GameModule, public Observer{
	public: 
		SimonSaysModule( LED* );
		bool isGameCompleted();
		uint8_t numberErrors();
		void init( uint8_t code );
		void updateModule();
		void terminate();
		void receiveDataFromSubject( Subject* );

	private: 
		// Used to display LEDS
		LED* leds;//Points to object that holds the data
		
		RandomNumber ranNum;

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

		// Sequence LEDS blink in
		uint32_t simonSaysSequence[ 10 ];

		// Sequence button needs to be pressed on 
		// Based on code word
		uint32_t buttonSequence[ 10 ];

		// Current position in Simon Says Sequence LED display
		// How many LEDs should be shown
		uint8_t simonSaysRound = 2;
		// Toggles between on and off
		uint8_t nextState = LOW; 

		// What is actually being displayed for LEDS
		uint8_t currentSSDisplay = 0;

		// How many buttons need to be pressed 
		uint8_t buttonRound = 2;

		// Used so it only recognizes button pressed once
		Bounce blue = Bounce();
		Bounce red = Bounce();
		Bounce green = Bounce();
		Bounce purple = Bounce();

		// Used to display sequence
		IntervalTimer simonSaysTimer;

		// Errors
		uint8_t errors = 0;
		
		// Code word
		uint8_t code = 0;

		// Game Won
		bool gameWon = false;

		void initializeLEDSequence();
		void initializeButtonSequence( uint8_t code );
		void initializeButtons();
		void initializeLEDs();
		void playSimonSays();
		void displaySimonSays();
		
		
};

#endif
