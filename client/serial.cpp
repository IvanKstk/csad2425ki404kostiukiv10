#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include "serial.h"

using namespace std;

HANDLE hSerial;
DCB dcbSerialParams = { 0 };
COMMTIMEOUTS timeouts = { 0 };

// Helper function to convert std::string to std::wstring
std::wstring stringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

void initSerialPort(const std::string& portName) {
    // Convert std::string to std::wstring
    std::wstring widePortName = stringToWString(portName);

    // Use CreateFileW for wide strings
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

void sendMessage(const char* message) {
    DWORD bytesWritten;
    WriteFile(hSerial, message, strlen(message), &bytesWritten, NULL);
    cout << "Sent by PC: " << message << endl;
}

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

void closeSerialPort() {
    CloseHandle(hSerial);
    cout << "Serial port closed." << endl;
}