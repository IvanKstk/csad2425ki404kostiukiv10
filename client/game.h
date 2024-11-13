/**
 * @file game.h
 * @brief Declares functions and global variables for managing game choices, state, and statistics.
 */

#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>

 /**
  * @brief Converts a numeric choice to the corresponding move string.
  *
  * @param number The number representing a move (1 for rock, 2 for scissors, 3 for paper).
  * @return std::string The string representation of the move ("rock", "scissors", or "paper").
  */
std::string getChoiceFromNumber(int number);

/**
 * @brief Gets the user's choice for the game (rock, scissors, or paper).
 *
 * Prompts the user to enter a number corresponding to a move and validates the input.
 *
 * @return std::string The string representation of the user's move ("rock", "scissors", or "paper").
 */
std::string getUserChoice();

/**
 * @brief Parses the response from Arduino to extract moves and results.
 *
 * Uses regular expressions to parse JSON-like formatted response from Arduino, extracting
 * the moves of Player 1 and Player 2, as well as the game result.
 *
 * @param response The response string received from Arduino.
 * @param player1 Reference to the string storing Player 1's move.
 * @param player2 Reference to the string storing Player 2's move or server move.
 * @param result Reference to the string storing the game result.
 */
void parseResponse(const std::string& response, std::string& player1, std::string& player2, std::string& result);

/**
 * @brief Saves the current game state to an XML file.
 *
 * Writes the game mode, player moves, result, and statistics to "game_state.xml". If the game mode has changed,
 * statistics are reset. This function is called after each game round to update the saved game state.
 *
 * @param player1 The move chosen by Player 1.
 * @param player2 The move chosen by Player 2.
 * @param result The result of the game round.
 * @param gameMode The current game mode (e.g., 1 for Man vs AI).
 * @param isLoadedGame If true, indicates the game was loaded from a saved state.
 */
void saveGameState(const std::string& player1, const std::string& player2, const std::string& result, int gameMode, bool isLoadedGame);

/**
 * @brief Loads the saved game state from an XML file.
 *
 * Reads the game mode, player moves, result, and statistics from "game_state.xml". If the file does not exist or
 * cannot be read, it returns false.
 *
 * @param player1 Reference to the string storing Player 1's last move.
 * @param player2 Reference to the string storing Player 2's last move.
 * @param result Reference to the string storing the last game result.
 * @param gameMode Reference to the integer storing the last game mode.
 * @return bool Returns true if the game state was loaded successfully; false otherwise.
 */
bool loadGameState(std::string& player1, std::string& player2, std::string& result, int& gameMode);

/**
 * @brief Gets a choice for the AI player from the server.
 *
 * This function retrieves the AI's move based on server logic.
 *
 * @return std::string The AI's chosen move ("rock", "scissors", or "paper").
 */
std::string getAIChoiceFromServer();




/**
 * @brief Resets game statistics, including win counts and total games.
 */
void resetStatistics();

extern int player1Wins;		/**< Number of wins by Player 1 */
extern int player2Wins;		/**< Number of wins by Player 2 */
extern int draws;			/**< Number of drawn games */
extern int totalGames;		/**< Total number of games played */
extern int currentGameMode;	/**< Current game mode */
extern int lastGameMode;	/**< Previous game mode, used to detect mode changes */

#endif