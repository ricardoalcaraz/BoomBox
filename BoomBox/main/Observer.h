class Subject;

class Observer {
	public:
		void attachSubject( Subject *subject );
		virtual void receiveDataFromSubject( Subject* subj ) = 0;
};
