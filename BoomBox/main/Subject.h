#ifndef Subject_h
#define Subject_h

#define SIZE 5

#include "Arduino.h"
class Observer;

/*Class to follow the observer design pattern and provide an easy avenue of alerting
 *other objects when a values has changed. Size is currently fixed at 5 but can be increased.
 */
class Subject {
	public:
		Subject();
		bool registerObserver( Observer *obs);
		void unregisterObserver( uint8_t ind );
		int16_t getVal();
		void setVal( int16_t val );
	
	private:
		int16_t val;
		void notifyObservers();
		Observer* observerList[SIZE];
		uint8_t currentInd;
};

#endif
