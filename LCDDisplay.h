#ifndef LCDDisplay_h
#define LCDDisplay_h
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

#include "Arduino.h"

// Name: LCD Display
// Author: Kristen Oduca
// Version: 1.0
// Notes: Display the code word on a LCD screen	

class LCDDisplay {
	public: 
		LCDDisplay();
		uint8_t getCode();
	private: 
		// Used to display LEDS
		LiquidCrystal_I2C lcd;
		uint32_t lcdRanNum;
			
		
};

#endif