#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "game.h"
#include "serial.h"

using namespace std;

// Global variables for statistics
int player1Wins = 0, player2Wins = 0, draws = 0, totalGames = 0;
int lastGameMode = -1;  // Initial value to determine the mode change

std::string getChoiceFromNumber(int number) {
    if (number == 1) return "rock";
    else if (number == 2) return "scissors";
    else if (number == 3) return "paper";
    return "";
}

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

void resetStatistics() {
    player1Wins = 0;
    player2Wins = 0;
    draws = 0;
    totalGames = 0;
}

void saveGameState(const std::string& player1, const std::string& player2, const std::string& result, int currentGameMode, bool resetStats = true) {
    if (resetStats && currentGameMode != lastGameMode) {
        resetStatistics();
        totalGames = 0;  // Reset the total number of games when changing the mode
        lastGameMode = currentGameMode;
    }

    if (!player1.empty() && !player2.empty()) {  // Increment totalGames only after the game is complete
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

    // Write to file
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