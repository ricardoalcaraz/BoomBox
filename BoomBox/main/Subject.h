#define SIZE 5

#include "Arduino.h"
class Observer;

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
