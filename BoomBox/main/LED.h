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
 */
 
class LED {
	public:
		static void init();
		static void update();
		static void setStatus(uint8_t status);
		static void setMorse1();
		static void setMorse2();
		static void clearMorse1();
		static void clearMorse2();
    static void setSSPin( uint8_t pin);
    static void setAllLEDS();
    static void clearAllLEDS();
	private:
		static uint8_t statusLEDs;
		static uint8_t byte1;
		static uint8_t byte2;
		static uint8_t byte3;
		static uint8_t byte4;
		static uint8_t byte5;
		static uint8_t SSPin;
};

#endif
