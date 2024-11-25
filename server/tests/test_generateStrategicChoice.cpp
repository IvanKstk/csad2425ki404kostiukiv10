#include <gtest/gtest.h>
#include "Server.h" 
#include "pch.h"

// Server wins "rock" (most "rock" in history)
TEST(GenerateStrategicChoiceTest, CountersRock) {
    player1History = { "rock", "rock", "scissors" };
    EXPECT_EQ(generateStrategicChoice(), "paper");
}

// Server wins "paper" (most "paper" in history)
TEST(GenerateStrategicChoiceTest, CountersPaper) {
    player1History = { "paper", "paper", "rock" };
    EXPECT_EQ(generateStrategicChoice(), "scissors");
}

// Server wins "scissors" (most "scissors" in history)
TEST(GenerateStrategicChoiceTest, CountersScissors) {
    player1History = { "scissors", "scissors", "paper" };
    EXPECT_EQ(generateStrategicChoice(), "rock");
}

// All elements are equivalent (e.g., ["rock", "paper", "scissors"])
TEST(GenerateStrategicChoiceTest, EqualDistribution) {
    player1History = { "rock", "paper", "scissors" };
    EXPECT_EQ(generateStrategicChoice(), "rock"); 
}

// Empty array (all elements are empty)
TEST(GenerateStrategicChoiceTest, EmptyHistory) {
    player1History = { "", "", "" };
    EXPECT_EQ(generateStrategicChoice(), "rock");
}