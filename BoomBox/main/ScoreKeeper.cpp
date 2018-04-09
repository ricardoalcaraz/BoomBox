#include "Arduino.h"
#include "ScoreKeeper.h"

/*ScoreKeeper constructor initializes all private variables to zero*/
ScoreKeeper::ScoreKeeper(uint8_t numGames, uint8_t numErrors) {
	this->errorLimit = numErrors;
	this->numGames = numGames;
	this->errorsMade = 0;
	this->numGamesCompleted = 0;
	this->gameWon = false;
	this->gameLost = false;
}

/*Increments error counter when this function is called and checks if the game has been lost*/
void ScoreKeeper::userMadeError() {
	this->errorsMade++;
	if( errorsMade >= errorLimit ) gameLost = true;
}

/*Updates number of errors based off the the input given*/
void ScoreKeeper::numErrors(uint8_t numErrorsMade) {
	this->errorsMade += numErrorsMade;
	if( errorsMade >= errorLimit ) gameLost = true;
}

/*Updates the game completed counter. If the counter reaches number of games then the gameWon status will be set to true*/
void ScoreKeeper::gameCompleted() {
	this->numGamesCompleted++;
	if( numGamesCompleted >= numGames ) gameWon = true;
}

/*Returns true if all games have been completed*/
bool ScoreKeeper::isGameWon() {
	return gameWon;
}

/*Returns true if the number of errors is greater then the error limit*/
bool ScoreKeeper::isGameLost() {
	return gameLost;
}

/*Return number of games won*/
uint8_t ScoreKeeper::getGamesWon() {
	return numGamesCompleted;
}

/*Return number of errors made*/
uint8_t ScoreKeeper::getErrorsMade() {
	return errorsMade;
}
