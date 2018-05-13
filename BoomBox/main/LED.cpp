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
  digitalWrite(2, HIGH); 
}

/*Set the 2nd Morse LED*/
void LED::setMorse2() {
  digitalWrite(3, HIGH); 
}

/*Clear only the morse 1 led in byte 1*/
void LED::clearMorse1() {
  digitalWrite(2, LOW); 
}

/*Clear only the morse 2 led in byte 1*/
void LED::clearMorse2() {
  digitalWrite(3, LOW); 
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
void LED::setStatus(uint8_t statusLED){
  // Clear all LEDS that is currently being display in byte 1 except the last two
  byte5 &= B00000011; 
  // Mask used to ensure last two LEDS won't accidentaly be set by by incoming byte
  const uint8_t statusMask = B11111100;
  // Clear the last two bits of incoming LED to esnure morse code is not being changed
  statusLED &= statusMask; 
  // Sets only the Simon Says LeD
  byte5 |= statusLED;
}

void LED::setButtonGameLEDS( uint8_t info ) {
  byte2 &= B00011111;
  const uint8_t statusMask = B11100000;
  info &= statusMask;
  byte2 |= info;
}

//Set a specific byte to display 
void LED::setByte1( uint8_t byte ) {
  byte1 = byte;
}

//Set a specific byte to display 
void LED::setByte2( uint8_t byte ) {
  byte2 = byte;
}

//Set a specific byte to display 
void LED::setByte3( uint8_t byte ) {
  byte3 = byte;
}

//Set a specific byte to display 
void LED::setByte4( uint8_t byte ) {
  byte4 = byte;
}

//Set a specific byte to display 
void LED::setByte5( uint8_t byte ) {
  byte5 = byte;
}
