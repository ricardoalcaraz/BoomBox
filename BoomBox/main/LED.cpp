#include "Arduino.h"
#include "LED.h"
#include "SPI.h"

LED::LED() {
	morseLEDs = 0;
	statusLEDs = 0;
	init();
	cutWireGame[0] = 0;
	cutWireGame[1] = 0;
	cutWireGame[2] = 0;
	cutWireGame[3] = 0;
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
  SPI.transfer(statusLEDs);
  SPI.transfer(cutWireGame[0]);
  SPI.transfer(cutWireGame[1]);
  SPI.transfer(cutWireGame[2]);
  SPI.transfer(cutWireGame[3]);
  digitalWrite(SSPin, HIGH);
}

/*Set the first Morse LED*/
void LED::setMorse1(bool state) {
	morseLEDs &= _BV(1);
	morseLEDs |= state<<1;
}

/*Set the 2nd Morse LED*/
void LED::setMorse2(bool state) {
	morseLEDs &= _BV(0);
	morseLEDs |= state;
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
