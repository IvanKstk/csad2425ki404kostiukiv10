#include <gtest/gtest.h>
#include "Server.h" 
#include "pch.h"

// Check if `player1Choice` and `player2Choice` are reset
TEST(ResetServerTest, ResetsPlayerChoices) {
    player1Choice = "rock";
    player2Choice = "paper";
    resetServer();
    EXPECT_EQ(player1Choice, "");
    EXPECT_EQ(player2Choice, "");
}

// Check if `player1History` is reset
TEST(ResetServerTest, ResetsPlayer1History) {
    player1History = { "rock", "paper", "scissors" };
    resetServer();
    EXPECT_EQ(player1History[0], "");
    EXPECT_EQ(player1History[1], "");
    EXPECT_EQ(player1History[2], "");
}

// Check if `historyIndex` is reset
TEST(ResetServerTest, ResetsHistoryIndex) {
    historyIndex = 2;
    resetServer();
    EXPECT_EQ(historyIndex, 0);
}