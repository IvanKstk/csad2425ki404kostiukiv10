#include "Server.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

std::string player1Choice = "";
std::string player2Choice = "";
std::vector<std::string> player1History(3, "");
int historyIndex = 0;

std::string generateServerChoice() {
    int choice = rand() % 3;
    if (choice == 0) return "rock";
    if (choice == 1) return "paper";
    return "scissors";
}

std::string generateStrategicChoice() {
    int rockCount = std::count(player1History.begin(), player1History.end(), "rock");
    int paperCount = std::count(player1History.begin(), player1History.end(), "paper");
    int scissorsCount = std::count(player1History.begin(), player1History.end(), "scissors");

    if (rockCount == 0 && paperCount == 0 && scissorsCount == 0) {
        return "rock";
    }

    if (rockCount == paperCount && rockCount == scissorsCount) {
        return "rock"; 
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

std::string determineResult(const std::string& player1, const std::string& player2) {
    if (player1 == player2) return "draw";

    if ((player1 == "rock" && player2 == "scissors") ||
        (player1 == "scissors" && player2 == "paper") ||
        (player1 == "paper" && player2 == "rock")) {
        return "Player 1 wins";
    }

    return "Player 2 wins";
}

void resetServer() {
    player1Choice = "";
    player2Choice = "";
    std::fill(player1History.begin(), player1History.end(), "");
    historyIndex = 0;
}