#include <iostream>
#include "menu.h"

using namespace std;

void menu() {
    cout << "\n============= Game Menu =============" << endl;
    cout << "1. Man vs AI" << endl;
    cout << "2. Man vs Man" << endl;
    cout << "3. AI vs AI (Random Move)" << endl;
    cout << "4. AI vs AI (Win Strategy)" << endl;
    cout << "5. Exit" << endl;  
    cout << "=====================================" << endl;
}

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