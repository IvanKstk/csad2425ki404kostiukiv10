#pragma once
#include <string>

void playManVsAI(std::string& player1, std::string& player2, std::string& result);
void playManVsMan(std::string& player1, std::string& player2, std::string& result);
void playAIVsAIRandom(std::string& player1, std::string& player2, std::string& result);
void playAIVsAIWinStrategy(std::string& player1, std::string& player2, std::string& result);
void displayResult(const std::string& player1, const std::string& player2, const std::string& result);