#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>

extern std::string player1Choice;
extern std::string player2Choice;
extern std::vector<std::string> player1History;
extern int historyIndex;

std::string generateServerChoice();
std::string generateStrategicChoice();
std::string determineResult(const std::string& player1, const std::string& player2);
void resetServer();

#endif // SERVER_H