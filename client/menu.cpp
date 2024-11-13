/**
 * @file menu.cpp
 * @brief Provides the game menu display function and validates user menu choices.
 */

#include <iostream>
#include "menu.h"

using namespace std;

/**
 * @brief Displays the game menu options.
 *
 * This function outputs the available game modes and the exit option, allowing the user
 * to select their preferred mode of play.
 */
void menu() {
    cout << "\n============= Game Menu =============" << endl;
    cout << "1. Man vs AI" << endl;
    cout << "2. Man vs Man" << endl;
    cout << "3. AI vs AI (Random Move)" << endl;
    cout << "4. AI vs AI (Win Strategy)" << endl;
    cout << "5. Exit" << endl;  
    cout << "=====================================" << endl;
}

/**
 * @brief Validates the user's choice input within a specified range.
 *
 * Prompts the user to enter a choice between the provided minimum and maximum values.
 * If the input is invalid (not within range or not an integer), the function displays an error
 * message and prompts the user again until a valid input is entered.
 *
 * @param min The minimum acceptable value for the choice.
 * @param max The maximum acceptable value for the choice.
 * @return int The validated user choice within the specified range.
 */
int getValidatedChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter choice: ";
        if (cin >> choice && choice >= min && choice <= max) {
            cin.ignore(10000, '\n');
            return choice;
        }
        else {
            cout << "[error] Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}