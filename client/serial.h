/**
 * @file serial.h
 * @brief Declares functions and variables for serial port communication, including initialization, sending, receiving, and closing the port.
 */

#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

extern HANDLE hSerial;	/**< Handle for the serial port connection. */

/**
 * @brief Initializes the serial port with specified settings.
 *
 * Opens the specified serial port, configures communication parameters such as baud rate and byte size,
 * and applies timeouts for read and write operations.
 *
 * @param portName The name of the serial port (e.g., "\\\\.\\COM3").
 */
void initSerialPort(const std::string& portName);

/**
 * @brief Sends a message over the serial port.
 *
 * Writes the provided message to the serial port.
 *
 * @param message A C-string representing the message to send.
 */
void sendMessage(const char* message);

/**
 * @brief Receives a message from the serial port.
 *
 * Reads data from the serial port into a buffer and returns it as a string.
 * If no data is read, an empty string is returned.
 *
 * @return std::string The message received from the serial port, or an empty string if no data was read.
 */
std::string receiveMessage();

/**
 * @brief Closes the serial port.
 *
 * Closes the handle to the serial port.
 */
void closeSerialPort();

#endif