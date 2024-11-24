#include <gtest/gtest.h>
#include "Server.h" 
#include <unordered_set>
#include <unordered_map>
#include "pch.h"

// Test 1: Check if the function returns only allowed values
TEST(GenerateServerChoiceTest, ReturnsValidChoices) {
    std::unordered_set<std::string> validChoices = { "rock", "paper", "scissors" };

    for (int i = 0; i < 100; ++i) { 
        std::string choice = generateServerChoice();
        EXPECT_TRUE(validChoices.find(choice) != validChoices.end())
            << "Invalid choice generated: " << choice;
    }
}

// Test 2: Check if all variants are generated evenly
TEST(GenerateServerChoiceTest, GeneratesAllChoices) {
    std::unordered_map<std::string, int> frequency = { {"rock", 0}, {"paper", 0}, {"scissors", 0} };
    int iterations = 1000; 

    for (int i = 0; i < iterations; ++i) {
        std::string choice = generateServerChoice();
        ++frequency[choice];
    }

    // Check if each option appears at least 25% of the total
    for (const auto& pair : frequency) {
        const std::string& choice = pair.first;
        int count = pair.second;
        EXPECT_GE(count, iterations / 4) << "Choice " << choice << " is underrepresented.";
    }
}