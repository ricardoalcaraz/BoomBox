#include "ObserverTester.h"
#include "Subject.h"

void ObserverTester::receiveDataFromSubject( Subject *subj ) {
	Serial.println("Val is "); Serial.println( subj->getVal () );
  digitalWrite( 23, digitalRead(23) ^ 1 );
}
