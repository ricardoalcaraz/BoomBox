#include "Observer.h"
#include "Subject.h"

/**Register the observer to a subject*/
void Observer::attachSubject( Subject *subject ) {
	subject->registerObserver( this );
}
