/**
 * @file game_logic.h
 * @brief Declares functions for different game modes (Man vs AI, Man vs Man, AI vs AI) and for displaying game results.
 */

#pragma once
#include <string>

/**
 * @brief Executes the "Man vs AI" game mode.
 *
 * Allows a human player to compete against the AI by obtaining the player's move, sending it to Arduino,
 * and receiving and processing the AI's response.
 *
 * @param player1 Reference to the string storing Player 1's move.
 * @param player2 Reference to the string storing Player 2's move (AI's move in this mode).
 * @param result Reference to the string storing the result of the game.
 */
void playManVsAI(std::string& player1, std::string& player2, std::string& result);

/**
 * @brief Executes the "Man vs Man" game mode.
 *
 * Facilitates a game between two human players by obtaining their moves, sending them to Arduino,
 * and processing the result received from Arduino.
 *
 * @param player1 Reference to the string storing Player 1's move.
 * @param player2 Reference to the string storing Player 2's move.
 * @param result Reference to the string storing the result of the game.
 */
void playManVsMan(std::string& player1, std::string& player2, std::string& result);

/**
 * @brief Executes the "AI vs AI (Random Move)" game mode.
 *
 * Simulates a match between two AI players making random moves. Sends a command to Arduino to execute
 * this AI vs AI mode and processes the response.
 *
 * @param player1 Reference to the string storing AI Player 1's move.
 * @param player2 Reference to the string storing AI Player 2's move.
 * @param result Reference to the string storing the result of the game.
 */
void playAIVsAIRandom(std::string& player1, std::string& player2, std::string& result);

/**
 * @brief Executes the "AI vs AI (Win Strategy)" game mode.
 *
 * Simulates a match between two AI players with a win-focused strategy. Sends a command to Arduino to
 * execute this AI vs AI mode and processes the response.
 *
 * @param player1 Reference to the string storing AI Player 1's move.
 * @param player2 Reference to the string storing AI Player 2's move.
 * @param result Reference to the string storing the result of the game.
 */
void playAIVsAIWinStrategy(std::string& player1, std::string& player2, std::string& result);

/**
 * @brief Displays the result of the game in a formatted manner.
 *
 * Outputs the choices made by each player and the result of the game. Uses colored text (if supported)
 * to highlight the winner's move.
 *
 * @param player1 The move chosen by Player 1.
 * @param player2 The move chosen by Player 2.
 * @param result The result of the game, indicating the winner or if it was a tie.
 */
void displayResult(const std::string& player1, const std::string& player2, const std::string& result);