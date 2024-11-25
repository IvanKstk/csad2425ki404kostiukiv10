#include <gtest/gtest.h>
#include <fstream>
#include <regex>
#include <sstream> // for std::cout
#include "game_logic.h"
#include "serial.h"
#include "game.h"
#include "pch.h"

// Test for getUserChoice
TEST(GameTest, GetUserChoiceTest) {
    // Cases of valid input
    {
        std::istringstream input("1\n");
        std::streambuf* origCin = std::cin.rdbuf(input.rdbuf()); 
        EXPECT_EQ(getUserChoice(), "rock");
        std::cin.rdbuf(origCin); 
    }

    {
        std::istringstream input("2\n");
        std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
        EXPECT_EQ(getUserChoice(), "scissors");
        std::cin.rdbuf(origCin);
    }

    {
        std::istringstream input("3\n");
        std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
        EXPECT_EQ(getUserChoice(), "paper");
        std::cin.rdbuf(origCin);
    }

    // Incorrect input case
    {
        std::istringstream input("0\n4\n-1\n2\n");
        std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
        EXPECT_EQ(getUserChoice(), "scissors"); // After several incorrect attempts returns "scissors"
        std::cin.rdbuf(origCin);
    }
}

// test getChoiceFromNumber
TEST(GameTest, GetChoiceFromNumberTest) {
    EXPECT_EQ(getChoiceFromNumber(1), "rock");
    EXPECT_EQ(getChoiceFromNumber(2), "scissors");
    EXPECT_EQ(getChoiceFromNumber(3), "paper");
    EXPECT_EQ(getChoiceFromNumber(4), ""); // Invalid number returns empty string
}

//test resetStatistics
TEST(GameTest, ResetStatisticsTest) {
    player1Wins = 5;
    player2Wins = 3;
    draws = 2;
    totalGames = 10;

    resetStatistics();

    EXPECT_EQ(player1Wins, 0);
    EXPECT_EQ(player2Wins, 0);
    EXPECT_EQ(draws, 0);
    EXPECT_EQ(totalGames, 0);
}

//test  parseResponse
TEST(GameTest, ParseResponseTest) {
    std::string player1, player2, result;

    std::string response = R"({"Player1": "rock", "Player2": "scissors", "Result": "Player 1 wins"})";
    parseResponse(response, player1, player2, result);

    EXPECT_EQ(player1, "rock");
    EXPECT_EQ(player2, "scissors");
    EXPECT_EQ(result, "Player 1 wins");

    response = R"({"Player1": "paper", "Server": "scissors", "Result": "Player 2 wins"})";
    parseResponse(response, player1, player2, result);

    EXPECT_EQ(player1, "paper");
    EXPECT_EQ(player2, "scissors");
    EXPECT_EQ(result, "Player 2 wins");
}

//test saveGameState
TEST(GameTest, SaveGameStateTest) {
    resetStatistics();

    // Test for "Player 1 wins"
    {
        std::string player1 = "rock";
        std::string player2 = "scissors";
        std::string result = "Player 1 wins";
        int gameMode = 1;

        saveGameState(player1, player2, result, gameMode, true);

        EXPECT_EQ(player1Wins, 1);
        EXPECT_EQ(player2Wins, 0);
        EXPECT_EQ(draws, 0);
        EXPECT_EQ(totalGames, 1);
    }

    // Test for "Player 2 wins"
    {
        std::string player1 = "scissors";
        std::string player2 = "rock";
        std::string result = "Player 2 wins";
        int gameMode = 1;

        saveGameState(player1, player2, result, gameMode, false);

        EXPECT_EQ(player1Wins, 1); 
        EXPECT_EQ(player2Wins, 1);
        EXPECT_EQ(draws, 0);
        EXPECT_EQ(totalGames, 2); 
    }

    // Test for "draw"
    {
        std::string player1 = "rock";
        std::string player2 = "rock";
        std::string result = "draw";
        int gameMode = 1;

        saveGameState(player1, player2, result, gameMode, false);

        EXPECT_EQ(player1Wins, 1);
        EXPECT_EQ(player2Wins, 1);
        EXPECT_EQ(draws, 1); 
        EXPECT_EQ(totalGames, 3); 
    }

    // Test for empty players
    {
        std::string player1 = "";
        std::string player2 = "";
        std::string result = "";
        int gameMode = 1;

        saveGameState(player1, player2, result, gameMode, false);

        EXPECT_EQ(player1Wins, 1); 
        EXPECT_EQ(player2Wins, 1);
        EXPECT_EQ(draws, 1);
        EXPECT_EQ(totalGames, 3); 
    }
}

//test  loadGameState
TEST(GameTest, LoadGameStateTest) {
    std::ofstream file("game_state.xml");
    file << R"(<?xml version="1.0"?>
<GameState>
    <GameMode>1</GameMode>
    <Game>
        <Player1>rock</Player1>
        <Player2>scissors</Player2>
        <Result>Player 1 wins</Result>
        <Statistics>
            <Player1Wins>3</Player1Wins>
            <Player2Wins>2</Player2Wins>
            <Draws>1</Draws>
            <TotalGames>6</TotalGames>
        </Statistics>
    </Game>
</GameState>)";
    file.close();

    std::string player1, player2, result;
    int gameMode;

    bool loaded = loadGameState(player1, player2, result, gameMode);

    EXPECT_TRUE(loaded);
    EXPECT_EQ(player1, "rock");
    EXPECT_EQ(player2, "scissors");
    EXPECT_EQ(result, "Player 1 wins");
    EXPECT_EQ(gameMode, 1);
    EXPECT_EQ(player1Wins, 3);
    EXPECT_EQ(player2Wins, 2);
    EXPECT_EQ(draws, 1);
    EXPECT_EQ(totalGames, 6);
}

TEST(GameTest, SaveGameStateFileOpenErrorTest) {
    std::string player1 = "rock";
    std::string player2 = "scissors";
    std::string result = "Player 1 wins";
    int gameMode = 1;

    // Simulate a situation where the file cannot be opened
    std::ofstream file("game_state.xml");
    file.close(); 

    // Make the file "inaccessible" 
    chmod("game_state.xml", 0444);

    std::ostringstream capturedCerr;
    std::streambuf* originalCerr = std::cerr.rdbuf(capturedCerr.rdbuf());

    saveGameState(player1, player2, result, gameMode, true);
    std::cerr.rdbuf(originalCerr);

    EXPECT_TRUE(capturedCerr.str().find("Error opening file for writing!") != std::string::npos);

    chmod("game_state.xml", 0644); 
    std::remove("game_state.xml"); 
}

TEST(GameTest, LoadGameStateFileNotFoundTest) {
    std::string player1, player2, result;
    int gameMode;

    std::remove("game_state.xml");
    std::ostringstream capturedCerr;
    std::streambuf* originalCerr = std::cerr.rdbuf(capturedCerr.rdbuf());

    bool loaded = loadGameState(player1, player2, result, gameMode);

    std::cerr.rdbuf(originalCerr);

    EXPECT_FALSE(loaded);
    EXPECT_TRUE(capturedCerr.str().find("No saved game found.") != std::string::npos);
}