#include "LED.h"

uint8_t LED::byte1 = 0;
uint8_t LED::byte2 = 0;
uint8_t LED::byte3 = 0;
uint8_t LED::byte4 = 0;
uint8_t LED::byte5 = 0;
uint8_t LED::SSPin = 10;

/*SPI initialization*/
void LED::init(){
    pinMode(SSPin, OUTPUT);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setDataMode(SPI_MODE0);		
}

void LED::setSSPin( uint8_t pin ) {
  SSPin = pin;
}
/*Update all the LEDS
 *First 30 bits will be the cut wire game
 *Next two bits will be the morse code
 *Final bits will be the status
 */
void LED::update() {
  digitalWrite(SSPin, LOW);
  SPI.transfer(byte1);
  SPI.transfer(byte2);
  SPI.transfer(byte3);
  SPI.transfer(byte4);
  SPI.transfer(byte5);
  digitalWrite(SSPin, HIGH);
}

/*Set the first Morse LED*/
//Morse LED will be the least two significant
//bits in byte 1
void LED::setMorse1() {
  byte1 |= B00000001;  
}

/*Set the 2nd Morse LED*/
void LED::setMorse2() {
  byte1 |= B00000010;
}

/*Clear only the morse 1 led in byte 1*/
void LED::clearMorse1() {
  byte1 &= B11111110; 
}

/*Clear only the morse 2 led in byte 1*/
void LED::clearMorse2() {
  byte1 &= B11111101;
}


void LED::setAllLEDS() {
  byte1 = 0xFF;
  byte2 = 0xFF;
  byte3 = 0xFF;
  byte4 = 0xFF;
  byte5 = 0xFF;
}

void LED::clearAllLEDS() {
  byte1 = 0;
  byte2 = 0;
  byte3 = 0;
  byte4 = 0;
  byte5 = 0;
}

/*Set the status LEDs
 *They are currently the 6 most significant bits
 * of byte 1*/
void LED::setStatus(uint8_t status){
  uint8_t statusMask = status;
  statusMask &= B11111100; //clear last two leds since these are the morse code leds
  byte1 |= statusMask;
}

void LED::setByte2( uint8_t info ) {
	byte2 = info;
}
