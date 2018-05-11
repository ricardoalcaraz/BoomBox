#include "ObserverTester.h"
#include "Subject.h"

/**Register the observer to a subject*/
void ObserverTester::receiveDataFromSubject( Subject *subj ) {
	Serial.print("Received: "); Serial.println(subj->getVal());
}
