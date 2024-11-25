#include <iostream>
#include <string>
#include "Server.h"

int main() {
    srand(static_cast<unsigned>(time(0))); 
    std::cout << "Server ready\n";

    std::string clientMessage;
    while (std::getline(std::cin, clientMessage)) {
        clientMessage.erase(clientMessage.find_last_not_of(" \n\r\t") + 1); 

        if (clientMessage.find("Player1:") == 0) {
            player1Choice = clientMessage.substr(8);
        }
        else if (clientMessage.find("Player2:") == 0) {
            player2Choice = clientMessage.substr(8);

            std::string result = determineResult(player1Choice, player2Choice);
            std::cout << "{ \"Player1\": \"" << player1Choice
                << "\", \"Player2\": \"" << player2Choice
                << "\", \"Result\": \"" << result << "\" }\n";

            player1Choice.clear();
            player2Choice.clear();
        }
        else if (clientMessage == "get_ai_choice") {
            std::cout << generateServerChoice() << "\n";
        }
        else if (clientMessage == "RESET") {
            resetServer();
            std::cout << "Server reset completed\n";
        }
        else {
            std::string serverChoice = generateServerChoice();
            std::string result = determineResult(clientMessage, serverChoice);
            std::cout << "{ \"Server\": \"" << serverChoice
                << "\", \"Result\": \"" << result << "\" }\n";
        }
    }
    return 0;
}