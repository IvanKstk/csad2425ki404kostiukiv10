String player1Choice = "";
String player2Choice = "";

// Player 1's move history for a winning strategy
String player1History[3] = {"", "", ""};
int historyIndex = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino ready");

  randomSeed(analogRead(0)); // Initialize the random number generator
}

void loop() {
  if (Serial.available() > 0) {
    String clientMessage = Serial.readString();
    clientMessage.trim();

    if (clientMessage.startsWith("Player1:")) {
      // Human vs. Human mode — we get player 1's choice
      player1Choice = clientMessage.substring(8);
    } 
    else if (clientMessage.startsWith("Player2:")) {
      // Human vs. Human mode — we get player 2's choice and process the result
      player2Choice = clientMessage.substring(8);

      //  result
      String result = determineResult(player1Choice, player2Choice);
      String response = "{ \"Player1\": \"" + player1Choice + "\", \"Player2\": \"" + player2Choice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);

      // Clear the selections for the new game
      player1Choice = "";
      player2Choice = "";
    } 
    else if (clientMessage == "get_ai_choice") {
      // For AI vs. AI or Human vs. AI mode
      String aiChoice = generateServerChoice();
      Serial.println(aiChoice); // Send the AI ​​selection to the client
    }
    else if (clientMessage == "AI_vs_AI_random") {
      // AI vs. AI mode with random selection for each player
      player1Choice = generateServerChoice();
      player2Choice = generateServerChoice();

      // result
      String result = determineResult(player1Choice, player2Choice);

      // Form and send the response
      String response = "{ \"Player1\": \"" + player1Choice + "\", \"Player2\": \"" + player2Choice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);

     // Clear the selections for the new game
      player1Choice = "";
      player2Choice = "";
    }
    else if (clientMessage == "AI_vs_AI_win_strategy") {
      // AI vs. AI mode using a winning strategy for player 2

      // The choice of player 1 is random
      player1Choice = generateServerChoice();

      // We remember the choice of player 1 in history
      player1History[historyIndex] = player1Choice;
      historyIndex = (historyIndex + 1) % 3;

     // Player 2's choice is strategic
      player2Choice = generateStrategicChoice();

      // result
      String result = determineResult(player1Choice, player2Choice);

      // Form and send the response
      String response = "{ \"Player1\": \"" + player1Choice + "\", \"Player2\": \"" + player2Choice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);

     // Clear the selections for the new game
      player1Choice = "";
      player2Choice = "";
    }
    else {
      // For Human vs. AI mode - player submits their choice, server generates AI choice
      String serverChoice = generateServerChoice();
      String result = determineResult(clientMessage, serverChoice);

      // Send server selection and result
      String response = "{ \"Server\": \"" + serverChoice + "\", \"Result\": \"" + result + "\" }";
      Serial.println(response);
    }
  }
}

String generateServerChoice() {
  int choice = random(3);
  if (choice == 0) return "rock";
  if (choice == 1) return "paper";
  return "scissors";
}

// Function that analyzes the history of player 1 and chooses the winning move
String generateStrategicChoice() {
  int rockCount = 0;
  int paperCount = 0;
  int scissorsCount = 0;

  // Analysis of the history of the last 3 moves of player 1
  for (int i = 0; i < 3; i++) {
    if (player1History[i] == "rock") rockCount++;
    else if (player1History[i] == "paper") paperCount++;
    else if (player1History[i] == "scissors") scissorsCount++;
  }

  // Choose a strategy for player 2 based on player 1's most common move
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

String determineResult(String player1, String player2) {
  if (player1 == player2) return "draw";

  if ((player1 == "rock" && player2 == "scissors") ||
      (player1 == "scissors" && player2 == "paper") ||
      (player1 == "paper" && player2 == "rock")) {
    return "Player 1 wins";
  }

  return "Player 2 wins";
}
