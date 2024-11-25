#include <gtest/gtest.h>
#include <sstream> // std::cout and std::cin
#include "menu.h"
#include "pch.h"

// test menu()

TEST(MenuTest, MenuOutputTest) {

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    menu();

    std::cout.rdbuf(oldCoutBuffer);

    std::string expectedOutput =
        "\n============= Game Menu =============\n"
        "1. Man vs AI\n"
        "2. Man vs Man\n"
        "3. AI vs AI (Random Move)\n"
        "4. AI vs AI (Win Strategy)\n"
        "5. Exit\n"
        "=====================================\n";

    EXPECT_EQ(output.str(), expectedOutput);
}

// test getValidatedChoice

TEST(MenuTest, GetValidatedChoiceTest) {
    {
        std::istringstream input("2\n");
        std::streambuf* origCin = std::cin.rdbuf(input.rdbuf()); 

        EXPECT_EQ(getValidatedChoice(1, 5), 2); 

        std::cin.rdbuf(origCin); 
    }

    {
        std::istringstream input("0\n6\n-1\n3\n");
        std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());

        EXPECT_EQ(getValidatedChoice(1, 5), 3); 

        std::cin.rdbuf(origCin);
    }

    // Case with incorrect data (letters)
    {
        std::istringstream input("abc\n2\n");
        std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());

        EXPECT_EQ(getValidatedChoice(1, 5), 2); 

        std::cin.rdbuf(origCin);
    }
}

TEST(MenuTest, GetValidatedChoiceInvalidInputTest) {
    std::istringstream input("abc\n-1\n6\n2\n");
    std::cin.rdbuf(input.rdbuf());

    int choice = getValidatedChoice(1, 5);

    EXPECT_EQ(choice, 2); 
}