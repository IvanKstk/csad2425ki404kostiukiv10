#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

extern HANDLE hSerial;

void initSerialPort(const std::string& portName);
void sendMessage(const char* message);
std::string receiveMessage();
void closeSerialPort();

#endif