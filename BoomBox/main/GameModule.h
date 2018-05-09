#ifndef GameModule_h
#define GameModule_h
/**Generic class that all game modules will use as a base
 * These functions are necessary to provide a standardized way
 * of updating the game modules and score.
 * As a rule, the modules should stay away from unterminated while loops
 * and delays to prevent hangups*/

class GameModule {
	public:
		GameModule( ){};
		virtual bool isGameCompleted()=0;
		virtual uint8_t numberErrors()=0;
		virtual void init( uint8_t code )=0;
		virtual void updateModule()=0;
		virtual void terminate()=0;
};

#endif
