#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

// Глобальна змінна для роботи з серійним портом
extern HANDLE hSerial;

// Оголошення функцій для роботи з серійним портом
void initSerialPort(const std::string& portName);
void sendMessage(const char* message);
std::string receiveMessage();
void closeSerialPort();

#endif // SERIAL_H
