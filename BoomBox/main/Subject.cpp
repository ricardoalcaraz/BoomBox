#include "Subject.h"
#include "Observer.h"

/*Construct the subject object*/
Subject::Subject() {
	this->currentInd = 0;
}

/*Register an observer to the list*/
bool Subject::registerObserver( Observer *obs ) {
	if( currentInd < 5 ) {
		observerList[currentInd] = obs;
		currentInd++;
		return true;
	} else {
		return false;
	}
}

/*Unregister and observer from the list*/
void Subject::unregisterObserver( uint8_t ind ) {
	observerList[ind] = nullptr;
}

/*Notify all observers of change*/
void Subject::notifyObservers() {
	for( int i = 0; i < SIZE; i++ ) {
		if( observerList[i] != nullptr ) {
			observerList[i]->receiveDataFromSubject(this);
		}
	}
}

/*Set internal value*/
void Subject::setVal( int16_t val ){
	this->val = val;
	notifyObservers();
}

/*Return held value*/
int16_t Subject::getVal() {
	return val;
}
