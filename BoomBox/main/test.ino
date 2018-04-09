void testScoreKeeper() {
  static uint8_t numberGames = 6;
  static uint8_t totalErrors = 6;
  score.gameCompleted();
  score.userMadeError();
  score.gameCompleted();

  Serial.print("Games Completed: ");Serial.println(score.getGamesWon());
  Serial.print("Errors Made: ");Serial.println(score.getErrorsMade());
  Serial.print("Game won status"); Serial.println( score.isGameWon() );
  Serial.print("Game lost status: ") ;Serial.println( score.isGameLost() );

  score.numErrors(2);
}

