/**
 * @file game.cpp
 * @brief Contains functions for managing game state, processing player choices, and handling game statistics.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "game.h"
#include "serial.h"

using namespace std;


int player1Wins = 0, player2Wins = 0, draws = 0, totalGames = 0;
int lastGameMode = -1;  

/**
 * @brief Converts a numeric choice to the corresponding move string.
 *
 * @param number The number representing a move (1 for rock, 2 for scissors, 3 for paper).
 * @return std::string The string representation of the move ("rock", "scissors", "paper").
 */
std::string getChoiceFromNumber(int number) {
    if (number == 1) return "rock";
    else if (number == 2) return "scissors";
    else if (number == 3) return "paper";
    return "";
}

/**
 * @brief Gets the user's choice for the game (rock, scissors, or paper).
 *
 * Prompts the user to enter a number corresponding to a move and validates the input.
 *
 * @return std::string The string representation of the user's move ("rock", "scissors", or "paper").
 */
std::string getUserChoice() {
    int choice;
    while (true) {
        std::cout << "Enter 1 for rock, 2 for scissors, or 3 for paper: ";
        if (std::cin >> choice && (choice >= 1 && choice <= 3)) {
            if (choice == 1) return "rock";
            if (choice == 2) return "scissors";
            return "paper";
        }
        else {
            std::cout << "[error] Invalid choice. Please enter 1, 2, or 3." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

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
void parseResponse(const std::string& response, std::string& player1, std::string& player2, std::string& result) {
    std::regex player1Regex("\"Player1\": \"(.*?)\"");
    std::regex player2Regex("\"Player2\": \"(.*?)\"");
    std::regex serverRegex("\"Server\": \"(.*?)\"");
    std::regex resultRegex("\"Result\": \"(.*?)\"");
    std::smatch match;

    if (std::regex_search(response, match, player1Regex) && match.size() > 1) {
        player1 = match.str(1);
    }

    if (std::regex_search(response, match, player2Regex) && match.size() > 1) {
        player2 = match.str(1);
    }
    else if (std::regex_search(response, match, serverRegex) && match.size() > 1) {
        player2 = match.str(1);
    }

    if (std::regex_search(response, match, resultRegex) && match.size() > 1) {
        result = match.str(1);
    }
}

/**
 * @brief Resets game statistics, including win counts and total games.
 */
void resetStatistics() {
    player1Wins = 0;
    player2Wins = 0;
    draws = 0;
    totalGames = 0;
}

/**
 * @brief Saves the current game state to an XML file.
 *
 * Writes the game mode, player moves, result, and statistics to "game_state.xml". If the game mode has changed,
 * statistics are reset. This function is called after each game round to update the saved game state.
 *
 * @param player1 The move chosen by Player 1.
 * @param player2 The move chosen by Player 2.
 * @param result The result of the game round.
 * @param currentGameMode The current game mode (e.g., 1 for Man vs AI).
 * @param resetStats If true, resets statistics when the game mode changes.
 */
void saveGameState(const std::string& player1, const std::string& player2, const std::string& result, int currentGameMode, bool resetStats = true) {
    if (resetStats && currentGameMode != lastGameMode) {
        resetStatistics();
        totalGames = 0;  
        lastGameMode = currentGameMode;
    }

    if (!player1.empty() && !player2.empty()) {  
        totalGames++;
        if (result == "Player 1 wins") {
            player1Wins++;
        }
        else if (result == "Player 2 wins") {
            player2Wins++;
        }
        else if (result == "draw") {
            draws++;
        }
    }

    std::ofstream file("game_state.xml");
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    file << "<?xml version=\"1.0\"?>\n";
    file << "<GameState>\n";
    file << "    <GameMode>" << currentGameMode << "</GameMode>\n";
    file << "    <Game>\n";
    file << "        <Player1>" << player1 << "</Player1>\n";
    file << "        <Player2>" << player2 << "</Player2>\n";
    file << "        <Result>" << result << "</Result>\n";
    file << "        <Statistics>\n";
    file << "            <Player1Wins>" << player1Wins << "</Player1Wins>\n";
    file << "            <Player2Wins>" << player2Wins << "</Player2Wins>\n";
    file << "            <Draws>" << draws << "</Draws>\n";
    file << "            <TotalGames>" << totalGames << "</TotalGames>\n";
    file << "        </Statistics>\n";
    file << "    </Game>\n";
    file << "</GameState>\n";

    file.close();
    std::cout << "Game state saved to game_state.xml" << std::endl;
}

/**
 * @brief Loads the saved game state from an XML file.
 *
 * Reads the game mode, player moves, result, and statistics from "game_state.xml". If the file does not exist or
 * cannot be read, it returns false.
 *
 * @param player1 Reference to the string storing Player 1's last move.
 * @param player2 Reference to the string storing Player 2's last move.
 * @param result Reference to the string storing the last game result.
 * @param currentGameMode Reference to the integer storing the last game mode.
 * @return bool Returns true if the game state was loaded successfully; false otherwise.
 */
bool loadGameState(std::string& player1, std::string& player2, std::string& result, int& currentGameMode) {
    std::ifstream file("game_state.xml");
    std::string line;
    bool hasData = false;

    if (!file.is_open()) {
        std::cerr << "No saved game found." << std::endl;
        return false;
    }

    std::regex modeRegex("<GameMode>(.*?)</GameMode>");
    std::regex player1Regex("<Player1>(.*?)</Player1>");
    std::regex player2Regex("<Player2>(.*?)</Player2>");
    std::regex resultRegex("<Result>(.*?)</Result>");
    std::regex player1WinsRegex("<Player1Wins>(\\d+)</Player1Wins>");
    std::regex player2WinsRegex("<Player2Wins>(\\d+)</Player2Wins>");
    std::regex drawsRegex("<Draws>(\\d+)</Draws>");
    std::regex totalGamesRegex("<TotalGames>(\\d+)</TotalGames>");
    std::smatch match;

    while (std::getline(file, line)) {
        if (std::regex_search(line, match, modeRegex) && match.size() > 1) {
            currentGameMode = std::stoi(match.str(1));
            hasData = true;
        }
        if (std::regex_search(line, match, player1Regex) && match.size() > 1) {
            player1 = match.str(1);
        }
        if (std::regex_search(line, match, player2Regex) && match.size() > 1) {
            player2 = match.str(1);
        }
        if (std::regex_search(line, match, resultRegex) && match.size() > 1) {
            result = match.str(1);
        }
        if (std::regex_search(line, match, player1WinsRegex) && match.size() > 1) {
            player1Wins = std::stoi(match.str(1));
        }
        if (std::regex_search(line, match, player2WinsRegex) && match.size() > 1) {
            player2Wins = std::stoi(match.str(1));
        }
        if (std::regex_search(line, match, drawsRegex) && match.size() > 1) {
            draws = std::stoi(match.str(1));
        }
        if (std::regex_search(line, match, totalGamesRegex) && match.size() > 1) {
            totalGames = std::stoi(match.str(1));
        }
    }

    file.close();
    return hasData;
}