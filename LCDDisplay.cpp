#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
#include "LCDDisplay.h"

#include "Arduino.h"

LCDDisplay::LCDDisplay() : lcd(LiquidCrystal_I2C(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE))  {
	
	String lcdWords[] = {"Fantasia", "diabolique", "diabolic", "none", "stop", "euripides"};
	Serial.begin(9600);  // Used to type in characters
	lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight 
	rngsetup();
	while(!Serial);
	Serial.println("Finished Setup");
	lcdRanNum = trng() % 7;
	lcd.setCursor(0,0); 
	lcd.print("Code Word");
	Serial.println(lcdRanNum);
	if ( lcdRanNum == 6 ) {
	} else {
	lcd.setCursor(0,1);
	lcd.print( lcdWords[ lcdRanNum ] );
	}
}


void LCDDisplay::getCode() {
	return lcdRanNum;
}