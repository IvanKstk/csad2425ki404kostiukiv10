#include <iostream>
#include <string>
#include "menu.h"
#include "game_logic.h"
#include "game.h"
#include "serial.h"

using namespace std;

int currentGameMode = -1;

void initializeNewGame(int gameMode) {
    currentGameMode = gameMode;
    resetStatistics();
    totalGames = 0;
    saveGameState("", "", "", currentGameMode, true); // Keeps the initial state with reset statistics
}

int main() {
    cout << "[info] Starting program..." << endl;
    initSerialPort("\\\\.\\COM3");
    cout << "[info] Serial port initialized." << endl;

    bool isLoadedGame = false;
    string player1, player2, result;
    int startChoice;

    cout << "Would you like to start a new game or load the saved game? (1 for New Game, 0 for Load Game): ";
    while (!(cin >> startChoice) || (startChoice != 1 && startChoice != 0)) {
        cout << "[error] Invalid input. Please enter 1 (New Game) or 0 (Load Game): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();

    if (startChoice == 1) {
        cout << "[info] Starting a new game." << endl;
        menu();
        int newGameMode = getValidatedChoice(1, 5);  
        if (newGameMode == 5) {
            cout << "[info] Exiting program..." << endl;
            closeSerialPort();
            return 0;
        }
        initializeNewGame(newGameMode);
        isLoadedGame = false;
    }
    else if (startChoice == 0) {
        cout << "[info] Loading saved game state" << endl;
        bool loadSuccess = loadGameState(player1, player2, result, currentGameMode);
        if (loadSuccess) {
            cout << "Game state loaded from game_state.xml" << endl;
            displayResult(player1, player2, result);
            isLoadedGame = true;
        }
        else {
            cout << "[info] No saved game found or error loading game state. Starting new game." << endl;
            menu();
            int newGameMode = getValidatedChoice(1, 5);  
            if (newGameMode == 5) {
                cout << "[info] Exiting program..." << endl;
                closeSerialPort();
                return 0;
            }
            initializeNewGame(newGameMode);
            isLoadedGame = false;
        }
    }

    while (true) {
        // After loading a saved game or selecting a new mode
        while (true) {
            switch (currentGameMode) {
            case 1:
                cout << "\n[info] Playing in Man vs AI mode" << endl;
                playManVsAI(player1, player2, result);
                break;
            case 2:
                cout << "\n[info] Playing in Man vs Man mode" << endl;
                playManVsMan(player1, player2, result);
                break;
            case 3:
                cout << "\n[info] Playing in AI vs AI (Random Move) mode" << endl;
                playAIVsAIRandom(player1, player2, result);
                break;
            case 4:
                cout << "\n[info] Playing in AI vs AI (Win Strategy) mode" << endl;
                playAIVsAIWinStrategy(player1, player2, result);
                break;
            }

            displayResult(player1, player2, result);
            saveGameState(player1, player2, result, currentGameMode, false);

            cout << "\nDo you want to play another round in this mode? (1 for Yes, 0 for No): ";
            int continueChoice;
            while (!(cin >> continueChoice) || (continueChoice != 0 && continueChoice != 1)) {
                cout << "[error] Invalid input. Please enter 1 (Yes) or 0 (No): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore();

            if (continueChoice == 0) {
                break;
            }
        }

        // Ask the user if they want to choose another mode or exit
        cout << "\nDo you want to select a different game mode or exit? (1 for Select Mode, 0 for Exit): ";
        int nextAction;
        while (!(cin >> nextAction) || (nextAction != 1 && nextAction != 0)) {
            cout << "[error] Invalid input. Please enter 1 (Select Mode) or 0 (Exit): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (nextAction == 0) {
            cout << "[info] Exiting program..." << endl;
            break;
        }
        else if (nextAction == 1) {
            menu();
            int newGameMode = getValidatedChoice(1, 5); 
            if (newGameMode == 5) {
                cout << "[info] Exiting program..." << endl;
                break;
            }
            initializeNewGame(newGameMode);
        }
    }

    closeSerialPort();
    cout << "[info] Program finished." << endl;
    return 0;
}
