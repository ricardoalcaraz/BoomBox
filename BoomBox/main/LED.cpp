#include "Arduino.h"
#include "LED.h"
#include "SPI.h"

LED::LED() {
	init();
	byte1 = 0;
	byte2 = 0;
	byte3 = 0;
	byte4 = 0;
	byte5 = 0;
}

/*SPI initialization*/
void LED::init(){
    pinMode(SSPin, OUTPUT);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setDataMode(SPI_MODE0);		
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
void LED::setMorse1() {
}

/*Set the 2nd Morse LED*/
void LED::setMorse2() {
}

/*Set the Cut Wire minigame LEDS*/
void LED::setWire(uint8_t arr[]){
	for(int i = 0; i < 4; i++) {
		cutWireGame[i] = arr[i];
	}
}

/*Set the status LEDs*/
void LED::setStatus(uint8_t status){
	statusLEDs = status;
}
