#include <Wire.h>  // Comes with Arduino IDE
#include "LCDDisplay.h"

#include "Arduino.h"

LCDDisplay::LCDDisplay() : lcd(LiquidCrystal_I2C(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE))  {
}


void LCDDisplay::init( uint32_t randNum ) {
  this->lcdRanNum = randNum;
  if( lcdRanNum > 7 ) {
    lcdRanNum = lcdRanNum % 7;
  }
  String lcdWords[] = {"Fantasia", "diabolique", "diabolic", "none", "stop", "euripides"};
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight 
  lcd.setCursor(0,0); 
  lcd.print("Code Word");
  if ( lcdRanNum == 6 ) {
  } else {
    lcd.setCursor(0,1);
    lcd.print( lcdWords[ lcdRanNum ] );
  }
}

uint8_t LCDDisplay::getCode() {
	return (uint8_t) lcdRanNum;
}
