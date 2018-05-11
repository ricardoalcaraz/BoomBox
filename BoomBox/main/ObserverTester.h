#ifndef ObserverTester_h
#define ObserverTester_h

#include "Observer.h"

/*Provides functionality to allow an object to get updated whenever a
 *value of interest changes
 */
class ObserverTester: public Observer {
	public:
		void receiveDataFromSubject( Subject* subj ) ;
};

#endif
