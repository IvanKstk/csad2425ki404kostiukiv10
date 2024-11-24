#include <gtest/gtest.h>
#include <sstream> // for test std::cout
#include "game_logic.h"
#include "serial.h"
#include "game.h"
#include "pch.h"

// Test to check the case where Player 1 wins
TEST(DisplayResultTest, Player1Wins) {
    std::string player1 = "Rock";
    std::string player2 = "Scissors";
    std::string result = "Player 1 wins";

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    displayResult(player1, player2, result);

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "\n========== Game Result ==========\n"
        "Player 1 chose: \033[32mRock\033[0m\n"
        "Player 2 chose: \033[31mScissors\033[0m\n"
        "Result: Player 1 wins\n"
        "=================================\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check the case where Player 2 wins 
TEST(DisplayResultTest, Player2Wins) {
    std::string player1 = "Scissors";
    std::string player2 = "Rock";
    std::string result = "Player 2 wins";

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    displayResult(player1, player2, result);

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "\n========== Game Result ==========\n"
        "Player 1 chose: \033[31mScissors\033[0m\n"
        "Player 2 chose: \033[32mRock\033[0m\n"
        "Result: Player 2 wins\n"
        "=================================\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

// test for draw
TEST(DisplayResultTest, Draw) {
    std::string player1 = "Paper";
    std::string player2 = "Paper";
    std::string result = "Draw";

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    displayResult(player1, player2, result);

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "\n========== Game Result ==========\n"
        "Player 1 chose: Paper\n"
        "Player 2 chose: Paper\n"
        "Result: Draw\n"
        "=================================\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

// Test for unknown result
TEST(DisplayResultTest, UnknownResult) {
    std::string player1 = "Rock";
    std::string player2 = "Paper";
    std::string result = "Unknown result";

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    displayResult(player1, player2, result);

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "\n========== Game Result ==========\n"
        "Player 1 chose: Rock\n"
        "Player 2 chose: Paper\n"
        "Result: Unknown result\n"
        "=================================\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

// Test for empty strings
TEST(DisplayResultTest, EmptyChoices) {
    std::string player1 = "";
    std::string player2 = "";
    std::string result = "Draw";

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    displayResult(player1, player2, result);

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "\n========== Game Result ==========\n"
        "Player 1 chose: \n"
        "Player 2 chose: \n"
        "Result: Draw\n"
        "=================================\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

// Test to check both empty choices with unknown result
TEST(DisplayResultTest, EmptyChoicesUnknownResult) {
    std::string player1 = "";
    std::string player2 = "";
    std::string result = "Unknown";

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    displayResult(player1, player2, result);

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "\n========== Game Result ==========\n"
        "Player 1 chose: \n"
        "Player 2 chose: \n"
        "Result: Unknown\n"
        "=================================\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

//test playManVsAI
#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "game_logic.h"
#include "serial.h"
#include "game.h"

// mocks for tests
std::string mockGetUserChoice() {
    return "Rock"; 
}

void mockSendMessage(const char* message) {
    EXPECT_STREQ(message, "Rock"); 
}

std::string mockReceiveMessagePlayer1Wins() {
    return "Player1:Rock;Player2:Scissors;Result:Player 1 wins"; 
}

std::string mockReceiveMessagePlayer2Wins() {
    return "Player1:Rock;Player2:Paper;Result:Player 2 wins"; 
}

std::string mockReceiveMessageDraw() {
    return "Player1:Rock;Player2:Rock;Result:Draw";
}

std::string mockReceiveMessageInvalid() {
    return "Invalid Response Format"; 
}

// // Override parseResponse for mocks
void mockParseResponse(const std::string& response, std::string& player1, std::string& player2, std::string& result) {
    if (response == "Player1:Rock;Player2:Scissors;Result:Player 1 wins") {
        player1 = "Rock";
        player2 = "Scissors";
        result = "Player 1 wins";
    }
    else if (response == "Player1:Rock;Player2:Paper;Result:Player 2 wins") {
        player1 = "Rock";
        player2 = "Paper";
        result = "Player 2 wins";
    }
    else if (response == "Player1:Rock;Player2:Rock;Result:Draw") {
        player1 = "Rock";
        player2 = "Rock";
        result = "Draw";
    }
    else {
        throw std::runtime_error("Invalid response format");
    }
}

// Modified function for testing
void playManVsAIMock(std::string& player1, std::string& player2, std::string& result, const std::string& response) {
    player1 = mockGetUserChoice();
    std::cout << "[info] Sending move to Arduino: " << player1 << std::endl;
    mockSendMessage(player1.c_str());
    std::cout << "[info] Receiving response from Arduino..." << std::endl;
    mockParseResponse(response, player1, player2, result);
}

// Tests
TEST(GameLogicTest, PlayManVsAITest_Player1Wins) {
    std::string player1, player2, result;

    playManVsAIMock(player1, player2, result, mockReceiveMessagePlayer1Wins());

    EXPECT_EQ(player1, "Rock");
    EXPECT_EQ(player2, "Scissors");
    EXPECT_EQ(result, "Player 1 wins");
}

TEST(GameLogicTest, PlayManVsAITest_Player2Wins) {
    std::string player1, player2, result;

    playManVsAIMock(player1, player2, result, mockReceiveMessagePlayer2Wins());

    EXPECT_EQ(player1, "Rock");
    EXPECT_EQ(player2, "Paper");
    EXPECT_EQ(result, "Player 2 wins");
}

TEST(GameLogicTest, PlayManVsAITest_Draw) {
    std::string player1, player2, result;

    playManVsAIMock(player1, player2, result, mockReceiveMessageDraw());

    EXPECT_EQ(player1, "Rock");
    EXPECT_EQ(player2, "Rock");
    EXPECT_EQ(result, "Draw");
}

TEST(GameLogicTest, PlayManVsAITest_InvalidResponse) {
    std::string player1, player2, result;

    EXPECT_THROW(playManVsAIMock(player1, player2, result, mockReceiveMessageInvalid()), std::runtime_error);
}

TEST(GameLogicTest, PlayManVsAITest_EmptyResponse) {
    std::string player1, player2, result;

    auto mockReceiveEmptyResponse = []() { return ""; };

    EXPECT_THROW(playManVsAIMock(player1, player2, result, mockReceiveEmptyResponse()), std::runtime_error);
}

TEST(GameLogicTest, PlayManVsAITest_UnexpectedInput) {
    std::string player1, player2, result;

    auto mockReceiveUnexpectedInput = []() { return "Unexpected:Data"; }; 

    EXPECT_THROW(playManVsAIMock(player1, player2, result, mockReceiveUnexpectedInput()), std::runtime_error);
}

// test playManVsMan

// mocks playManVsMan
std::string mockGetUserChoicePlayer1() {
    return "Paper"; 
}

std::string mockGetUserChoicePlayer2() {
    return "Rock"; 
}

void mockSendMessageManVsMan(const char* message) {
    std::string msg(message);
    if (msg.find("Player1:") != std::string::npos) {
        EXPECT_EQ(msg, "Player1:Paper");
    }
    else if (msg.find("Player2:") != std::string::npos) {
        EXPECT_EQ(msg, "Player2:Rock");
    }
}

std::string mockReceiveMessageManVsMan() {
    return "Player1:Paper;Player2:Rock;Result:Player 1 wins"; 
}

void mockParseResponseManVsMan(const std::string& response, std::string& player1, std::string& player2, std::string& result) {
    EXPECT_EQ(response, "Player1:Paper;Player2:Rock;Result:Player 1 wins");
    player1 = "Paper";
    player2 = "Rock";
    result = "Player 1 wins";
}

// 
void playManVsManMock(std::string& player1, std::string& player2, std::string& result) {
    player1 = mockGetUserChoicePlayer1();
    mockSendMessageManVsMan(("Player1:" + player1).c_str());
    Sleep(1000);

    system("CLS");

    player2 = mockGetUserChoicePlayer2();
    mockSendMessageManVsMan(("Player2:" + player2).c_str());
    Sleep(1000);

    std::string response = mockReceiveMessageManVsMan();
    mockParseResponseManVsMan(response, player1, player2, result);
}

// test for playManVsMan
TEST(GameLogicTest, PlayManVsManTest) {
    std::string player1, player2, result;

    playManVsManMock(player1, player2, result);

    EXPECT_EQ(player1, "Paper");
    EXPECT_EQ(player2, "Rock");
    EXPECT_EQ(result, "Player 1 wins");
}

// test AIvsAI

// mocks for playAIVsAIRandom
void mockSendMessageAIRandom(const char* message) {
    EXPECT_STREQ(message, "AI_vs_AI_random");
}

std::string mockReceiveMessageAIRandom() {
    return "Player1:Rock;Player2:Scissors;Result:Player 1 wins";
}

void mockParseResponseAIRandom(const std::string& response, std::string& player1, std::string& player2, std::string& result) {
    EXPECT_EQ(response, "Player1:Rock;Player2:Scissors;Result:Player 1 wins");
    player1 = "Rock";
    player2 = "Scissors";
    result = "Player 1 wins";
}

// Modified function for testing
void playAIVsAIRandomMock(std::string& player1, std::string& player2, std::string& result) {
    mockSendMessageAIRandom("AI_vs_AI_random");
    Sleep(1000);

    std::cout << "[info] Receiving response from mock server..." << std::endl;
    std::string response = mockReceiveMessageAIRandom();
    mockParseResponseAIRandom(response, player1, player2, result);
}

// test for playAIVsAIRandom
TEST(GameLogicTest, PlayAIVsAIRandomTest) {
    std::string player1, player2, result;

    playAIVsAIRandomMock(player1, player2, result);

    EXPECT_EQ(player1, "Rock");
    EXPECT_EQ(player2, "Scissors");
    EXPECT_EQ(result, "Player 1 wins");
}

// test AIvsAI win strategy

// mocks for playAIVsAIWinStrategy
void mockSendMessageAIWinStrategy(const char* message) {
    EXPECT_STREQ(message, "AI_vs_AI_win_strategy");
}

std::string mockReceiveMessageAIWinStrategy() {
    return "Player1:Paper;Player2:Rock;Result:Player 1 wins";
}

void mockParseResponseAIWinStrategy(const std::string& response, std::string& player1, std::string& player2, std::string& result) {
    EXPECT_EQ(response, "Player1:Paper;Player2:Rock;Result:Player 1 wins");
    player1 = "Paper";
    player2 = "Rock";
    result = "Player 1 wins";
}

// Modified function for testing
void playAIVsAIWinStrategyMock(std::string& player1, std::string& player2, std::string& result) {
    mockSendMessageAIWinStrategy("AI_vs_AI_win_strategy");
    Sleep(1000);

    std::cout << "[info] Receiving response from mock server..." << std::endl;
    std::string response = mockReceiveMessageAIWinStrategy();
    mockParseResponseAIWinStrategy(response, player1, player2, result);
}

// test for playAIVsAIWinStrategy
TEST(GameLogicTest, PlayAIVsAIWinStrategyTest) {
    std::string player1, player2, result;

    playAIVsAIWinStrategyMock(player1, player2, result);

    EXPECT_EQ(player1, "Paper");
    EXPECT_EQ(player2, "Rock");
    EXPECT_EQ(result, "Player 1 wins");
}