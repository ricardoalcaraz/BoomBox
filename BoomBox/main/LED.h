#ifndef LED_h 
#define LED_h

#include "Arduino.h"
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
 * SHIFT REGISTER Pins
 * SCLK - SCLK
 * SER  - MOSI
 * RCLK - SS
 */
 
class LED {
	public:
		LED();
		void init();
		void update();
		void setStatus(uint8_t status);
		void setWire(uint8_t arr[]);
		void setMorse1(bool state);
		void setMorse2(bool state);
	private:
		uint8_t statusLEDs;
		uint8_t morseLEDs;
		uint8_t cutWireGame[4];
		const uint8_t SSPin = 10;
};

#endif
