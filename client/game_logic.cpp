#include <iostream>
#include <string>
#include <regex>
#include "game_logic.h"
#include "game.h"
#include "serial.h"

using namespace std;

void playManVsAI(string& player1, string& player2, string& result) {
    player1 = getUserChoice();
    cout << "[info] Sending move to Arduino: " << player1 << endl;
    sendMessage(player1.c_str());
    Sleep(1000);

    cout << "[info] Receiving response from Arduino..." << endl;
    string response = receiveMessage();
    parseResponse(response, player1, player2, result); 
}

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

void playAIVsAIRandom(string& player1, string& player2, string& result) {
    sendMessage("AI_vs_AI_random");
    Sleep(1000);

    cout << "[info] Receiving response from Arduino..." << endl;
    string response = receiveMessage();
    parseResponse(response, player1, player2, result); 
}

void playAIVsAIWinStrategy(string& player1, string& player2, string& result) {
    sendMessage("AI_vs_AI_win_strategy");
    Sleep(1000);

    cout << "[info] Receiving response from Arduino..." << endl;
    string response = receiveMessage();
    parseResponse(response, player1, player2, result); 
}

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
