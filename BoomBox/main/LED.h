#ifndef LED_h 
#define LED_h

#include "Arduino.h"
#include "SPI.h"
//**************************************************************//
//  Name    : SPI LEDs                                          //
//  Author  : Ricardo Alcaraz                                   //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to display switches                               //
//****************************************************************

/*
 * TEENSY 3.6 Pins
 * MOSI - 11
 * MISO - 12
 * SS   - 10
 * SCLK - 13
 * SHIFT REGISTER Pins from top to bottom
 * SER  - MOSI
 * RCLK - SS
 * SCLK - SCLK
 * TOP FROM BOTTOM 
 * 11
 * GREEN - 10
 * 13
 */
 
class LED {
	public:
		//Initialize the display, should only be called once
		static void init();
		//Update the display
		//Should only be called in the main loop
		static void update();

		//Set the status LEDs
		static void setStatus(uint8_t status);

		//Function to set the morse LED
		static void setMorse1();
		static void setMorse2();
		static void clearMorse1();
		static void clearMorse2();
    static void setSSPin( uint8_t pin);

		//Set all the LEDS to be on
        static void setAllLEDS();
		//Turn all the LEDs off
        static void clearAllLEDS();

		//Functions should be added to support the rest of the games
		static void setButtonGameLEDS( uint8_t info );
    static void setByte1(uint8_t byte);
    static void setByte2(uint8_t byte);
    static void setByte3(uint8_t byte);
    static void setByte4(uint8_t byte);
    static void setByte5(uint8_t byte);
	private:
		//least significant 2 bits are used for morse code
		//most significant 5 bits are used for simon says
		//One bit unused
		static uint8_t byte1;
		//All unused so far
		static uint8_t byte2;
		//All unused so far
		static uint8_t byte3;
		//All unused so far
		static uint8_t byte4;
		//All unused so far
		static uint8_t byte5;
		//select pin
		static uint8_t SSPin;
};

#endif
