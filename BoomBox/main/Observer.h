#ifndef Observer_h
#define Observer_h

class Subject;

/*Provides functionality to allow an object to get updated whenever a
 *value of interest changes
 */
class Observer {
	public:
		void attachSubject( Subject *subject );
		virtual void receiveDataFromSubject( Subject* subj ) = 0;
};

#endif
