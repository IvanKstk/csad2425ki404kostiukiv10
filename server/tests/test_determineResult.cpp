#include <gtest/gtest.h>
#include "Server.h" 
#include <unordered_set>
#include <unordered_map>
#include "pch.h"

// Player 1 wins
TEST(DetermineResultTest, Player1Wins) {
    EXPECT_EQ(determineResult("rock", "scissors"), "Player 1 wins");
    EXPECT_EQ(determineResult("scissors", "paper"), "Player 1 wins");
    EXPECT_EQ(determineResult("paper", "rock"), "Player 1 wins");
}

// Player 2 wins
TEST(DetermineResultTest, Player2Wins) {
    EXPECT_EQ(determineResult("scissors", "rock"), "Player 2 wins");
    EXPECT_EQ(determineResult("paper", "scissors"), "Player 2 wins");
    EXPECT_EQ(determineResult("rock", "paper"), "Player 2 wins");
}

// Draw
TEST(DetermineResultTest, Draw) {
    EXPECT_EQ(determineResult("rock", "rock"), "draw");
    EXPECT_EQ(determineResult("scissors", "scissors"), "draw");
    EXPECT_EQ(determineResult("paper", "paper"), "draw");
}