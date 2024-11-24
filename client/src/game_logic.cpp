/**
 * @file game_logic.cpp
 * @brief Contains functions to manage different game modes (Man vs AI, Man vs Man, AI vs AI) and display game results.
 */

#include <iostream>
#include <string>
#include <regex>
#include "game_logic.h"
#include "game.h"
#include "serial.h"

using namespace std;

/**
 * @brief Executes the "Man vs AI" game mode.
 *
 * This function allows a human player to play against the AI by sending the player's move to the Arduino,
 * waiting for the AI's response, and processing the result.
 *
 * @param player1 Reference to the string storing Player 1's move.
 * @param player2 Reference to the string storing Player 2's move (AI's move in this mode).
 * @param result Reference to the string storing the result of the game.
 */
void playManVsAI(string& player1, string& player2, string& result) {
    player1 = getUserChoice();
    cout << "[info] Sending move to Arduino: " << player1 << endl;
    sendMessage(player1.c_str());
    Sleep(1000);

    cout << "[info] Receiving response from Arduino..." << endl;
    string response = receiveMessage();
    parseResponse(response, player1, player2, result); 
}

/**
 * @brief Executes the "Man vs Man" game mode.
 *
 * This function allows two human players to play against each other by taking their moves and sending them to the Arduino.
 * The function then waits for the response from Arduino and processes the result.
 *
 * @param player1 Reference to the string storing Player 1's move.
 * @param player2 Reference to the string storing Player 2's move.
 * @param result Reference to the string storing the result of the game.
 */
void playManVsMan(string& player1, string& player2, string& result) {
    player1 = getUserChoice();
    sendMessage(("Player1:" + player1).c_str());
    Sleep(1000);

    system("CLS");

    player2 = getUserChoice();
    sendMessage(("Player2:" + player2).c_str());
    Sleep(1000);

    string response = receiveMessage();
    parseResponse(response, player1, player2, result); 
}

/**
 * @brief Executes the "AI vs AI (Random Move)" game mode.
 *
 * In this mode, two AI players compete against each other, making random moves. The function sends
 * a command to the Arduino to simulate an AI vs AI match and processes the result.
 *
 * @param player1 Reference to the string storing AI Player 1's move.
 * @param player2 Reference to the string storing AI Player 2's move.
 * @param result Reference to the string storing the result of the game.
 */
void playAIVsAIRandom(string& player1, string& player2, string& result) {
    sendMessage("AI_vs_AI_random");
    Sleep(1000);

    cout << "[info] Receiving response from Arduino..." << endl;
    string response = receiveMessage();
    parseResponse(response, player1, player2, result); 
}

/**
 * @brief Executes the "AI vs AI (Win Strategy)" game mode.
 *
 * This mode pits two AI players against each other with a win-focused strategy.
 * The function sends a command to the Arduino to simulate this type of AI vs AI match and processes the result.
 *
 * @param player1 Reference to the string storing AI Player 1's move.
 * @param player2 Reference to the string storing AI Player 2's move.
 * @param result Reference to the string storing the result of the game.
 */
void playAIVsAIWinStrategy(string& player1, string& player2, string& result) {
    sendMessage("AI_vs_AI_win_strategy");
    Sleep(1000);

    cout << "[info] Receiving response from Arduino..." << endl;
    string response = receiveMessage();
    parseResponse(response, player1, player2, result); 
}

/**
 * @brief Displays the result of the game in a formatted manner.
 *
 * This function outputs the choices made by each player and the result of the game.
 * It uses colored text (if supported) to indicate the winner's move.
 *
 * @param player1 The move chosen by Player 1.
 * @param player2 The move chosen by Player 2.
 * @param result The result of the game, indicating the winner or if it was a tie.
 */
void displayResult(const string& player1, const string& player2, const string& result) {
    const string GREEN = "\033[32m";
    const string RED = "\033[31m";
    const string RESET = "\033[0m";

    cout << "\n========== Game Result ==========" << endl;
    if (result == "Player 1 wins") {
        cout << "Player 1 chose: " << GREEN << player1 << RESET << endl;
        cout << "Player 2 chose: " << RED << player2 << RESET << endl;
    }
    else if (result == "Player 2 wins") {
        cout << "Player 1 chose: " << RED << player1 << RESET << endl;
        cout << "Player 2 chose: " << GREEN << player2 << RESET << endl;
    }
    else {
        cout << "Player 1 chose: " << player1 << endl;
        cout << "Player 2 chose: " << player2 << endl;
    }
    cout << "Result: " << result << endl;
    cout << "=================================" << endl;
}
