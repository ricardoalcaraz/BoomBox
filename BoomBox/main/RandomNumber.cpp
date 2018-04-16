
#include "Arduino.h"
#include "RandomNumber.h"

RandomNumber::RandomNumber(  ) {
	SIM_SCGC6 |= SIM_SCGC6_RNGA; // enable RNG
    PRREG(SIM_SCGC6);
    RNG_CR &= ~RNG_CR_SLP_MASK;
    RNG_CR |= RNG_CR_HA_MASK;  // high assurance, not needed
    PRREG(RNG_CR);
    PRREG(RNG_SR);
}

uint8_t RandomNumber::trng() {
	RNG_CR |= RNG_CR_GO_MASK;
    while((RNG_SR & RNG_SR_OREG_LVL(0xF)) == 0); // wait
    return RNG_OR;
}
