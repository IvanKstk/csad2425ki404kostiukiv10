/**
 * @file menu.h
 * @brief Declares functions for displaying the game menu and validating user input.
 */

#pragma once

 /**
  * @brief Displays the game menu options.
  *
  * Outputs the available game modes and the exit option, allowing the user
  * to select their preferred mode of play.
  */
void menu();

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
int getValidatedChoice(int min, int max);