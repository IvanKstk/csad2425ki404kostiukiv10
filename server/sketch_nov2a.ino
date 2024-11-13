/**
 * @file sketch_nov2a
 * @brief Implements the game logic for Rock-Paper-Scissors on Arduino, supporting different modes like Human vs. AI, AI vs. AI with random moves, and AI vs. AI with a winning strategy.
 */

String player1Choice = "";
String player2Choice = "";

String player1History[3] = {"", "", ""};
int historyIndex = 0;

/**
 * @brief Sets up the Arduino for serial communication and initializes the random number generator.
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Arduino ready");

  randomSeed(analogRead(0)); 
}

/**
 * @brief Main loop that checks for serial messages and processes game actions based on the received commands.
 * 
 * Supports various game modes:
 * - Human vs. Human: receives moves from both players.
 * - Human vs. AI: receives Player 1's move and generates an AI move.
 * - AI vs. AI (random): both players make random moves.
 * - AI vs. AI (win strategy): Player 1's move is random, while Player 2 makes a strategic move based on Player 1's history.
 */
void loop() {
  if (Serial.available() > 0) {
    String clientMessage = Serial.readString();
    clientMessage.trim();

    if (clientMessage.startsWith("Player1:")) {
      player1Choice = clientMessage.substring(8);
    } 
    else if (clientMessage.startsWith("Player2:")) {
      player2Choice = clientMessage.substring(8);

      String result = determineResult(player1Choice, player2Choice);
      String response = "{ \"Player1\": \"" + player1Choice + "\", \"Player2\": \"" + player2Choice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);

      player1Choice = "";
      player2Choice = "";
    } 
    else if (clientMessage == "get_ai_choice") {
      String aiChoice = generateServerChoice();
      Serial.println(aiChoice); 
    }
    else if (clientMessage == "AI_vs_AI_random") {
      player1Choice = generateServerChoice();
      player2Choice = generateServerChoice();

      String result = determineResult(player1Choice, player2Choice);

      String response = "{ \"Player1\": \"" + player1Choice + "\", \"Player2\": \"" + player2Choice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);

      player1Choice = "";
      player2Choice = "";
    }
    else if (clientMessage == "AI_vs_AI_win_strategy") {

      player1Choice = generateServerChoice();

      player1History[historyIndex] = player1Choice;
      historyIndex = (historyIndex + 1) % 3;

      player2Choice = generateStrategicChoice();

      String result = determineResult(player1Choice, player2Choice);

      String response = "{ \"Player1\": \"" + player1Choice + "\", \"Player2\": \"" + player2Choice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);

      player1Choice = "";
      player2Choice = "";
    }
    else {
      String serverChoice = generateServerChoice();
      String result = determineResult(clientMessage, serverChoice);

      String response = "{ \"Server\": \"" + serverChoice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);
    }
  }
}

/**
 * @brief Generates a random move for the server (either "rock", "paper", or "scissors").
 * 
 * @return String The generated move.
 */
String generateServerChoice() {
  int choice = random(3);
  if (choice == 0) return "rock";
  if (choice == 1) return "paper";
  return "scissors";
}

/**
 * @brief Generates a strategic choice for Player 2 based on Player 1's recent history.
 * 
 * Analyzes Player 1's last three moves and chooses a move that would most likely win against Player 1's most common move.
 * 
 * @return String The strategic move for Player 2.
 */
String generateStrategicChoice() {
  int rockCount = 0;
  int paperCount = 0;
  int scissorsCount = 0;

  
  for (int i = 0; i < 3; i++) {
    if (player1History[i] == "rock") rockCount++;
    else if (player1History[i] == "paper") paperCount++;
    else if (player1History[i] == "scissors") scissorsCount++;
  }

  if (rockCount >= paperCount && rockCount >= scissorsCount) {
    return "paper";  
  }
  else if (paperCount >= rockCount && paperCount >= scissorsCount) {
    return "scissors";  
  }
  else {
    return "rock";  
  }
}

/**
 * @brief Determines the result of a game round based on the moves of Player 1 and Player 2.
 * 
 * @param player1 The move chosen by Player 1.
 * @param player2 The move chosen by Player 2.
 * @return String The result of the game ("Player 1 wins", "Player 2 wins", or "draw").
 */
String determineResult(String player1, String player2) {
  if (player1 == player2) return "draw";

  if ((player1 == "rock" && player2 == "scissors") ||
      (player1 == "scissors" && player2 == "paper") ||
      (player1 == "paper" && player2 == "rock")) {
    return "Player 1 wins";
  }

  return "Player 2 wins";
}