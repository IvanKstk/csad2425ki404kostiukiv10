#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>

std::string getChoiceFromNumber(int number);
std::string getUserChoice();
void parseResponse(const std::string& response, std::string& player1, std::string& player2, std::string& result);
void saveGameState(const std::string& player1, const std::string& player2, const std::string& result, int gameMode, bool isLoadedGame);
bool loadGameState(std::string& player1, std::string& player2, std::string& result, int& gameMode); // Змінено підпис функції
std::string getAIChoiceFromServer();
extern int lastGameMode;
void resetStatistics();

// Змінні для підрахунку статистики
extern int player1Wins;
extern int player2Wins;
extern int draws;
extern int totalGames;
extern int currentGameMode;

#endif