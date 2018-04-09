#ifndef ScoreKeeper_h
#define LED_h

#include "Arduino.h"

/*Keeps track of the number of errors the user has made*/

class ScoreKeeper {
	public: 
			ScoreKeeper(uint8_t numGames, uint8_t numErrors);
			void userMadeError();
			void numErrors(uint8_t numErrorsMade);
			void gameCompleted();
			uint8_t getGamesWon();
			uint8_t getErrorsMade();
			bool isGameWon();
			bool isGameLost();
	private:
			uint8_t errorLimit;
			uint8_t errorsMade;
			uint8_t numGames;
			uint8_t numGamesCompleted;
			bool gameWon;
			bool gameLost;
};


#endif
