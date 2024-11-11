/**
 * @file serial.cpp
 * @brief Provides functions for serial port communication, including initialization, sending, and receiving messages.
 */

#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include "serial.h"

using namespace std;

HANDLE hSerial;
DCB dcbSerialParams = { 0 };
COMMTIMEOUTS timeouts = { 0 };

/**
 * @brief Helper function to convert a std::string to a std::wstring.
 *
 * Converts a standard string to a wide string to enable compatibility with Windows API functions that require wide strings.
 *
 * @param str The input string to convert.
 * @return std::wstring The converted wide string.
 */
std::wstring stringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

/**
 * @brief Initializes the serial port with specified settings.
 *
 * Opens the specified serial port, sets communication parameters such as baud rate and byte size, and applies timeouts.
 *
 * @param portName The name of the serial port (e.g., "\\\\.\\COM3").
 */
void initSerialPort(const std::string& portName) {
    std::wstring widePortName = stringToWString(portName);

    hSerial = CreateFileW(widePortName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Failed to open port!" << endl;
        exit(1);
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    cout << "Serial port configured." << endl;
}

/**
 * @brief Sends a message over the serial port.
 *
 * Writes the provided message to the serial port and displays it in the console.
 *
 * @param message A C-string representing the message to send.
 */
void sendMessage(const char* message) {
    DWORD bytesWritten;
    WriteFile(hSerial, message, strlen(message), &bytesWritten, NULL);
    cout << "Sent by PC: " << message << endl;
}

/**
 * @brief Receives a message from the serial port.
 *
 * Reads data from the serial port into a buffer and returns it as a string. If no data is read, returns an empty string.
 *
 * @return std::string The message received from the serial port, or an empty string if no data was read.
 */
std::string receiveMessage() {
    char buffer[1024] = { 0 };
    DWORD bytesRead;
    bool readSuccess = ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL);

    if (readSuccess && bytesRead > 0) {
        return string(buffer);
    }
    else {
        return "";
    }
}

/**
 * @brief Closes the serial port.
 *
 * Closes the handle to the serial port and displays a message in the console.
 */
void closeSerialPort() {
    CloseHandle(hSerial);
    cout << "Serial port closed." << endl;
}