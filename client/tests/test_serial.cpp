#include <gtest/gtest.h>
#include "serial.h"
#include <string>
#include <windows.h>
#include "pch.h"

HANDLE hMockSerial = (HANDLE)1;

HANDLE MockCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    if (std::wstring(lpFileName) == L"COM3") { 
        return hMockSerial;
    }
    return INVALID_HANDLE_VALUE;
}

BOOL MockWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped) {
    if (hFile == hMockSerial) {
        *lpNumberOfBytesWritten = nNumberOfBytesToWrite;
        return TRUE;
    }
    return FALSE;
}

BOOL MockReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped) {
    if (hFile == hMockSerial) {
        std::string mockResponse = "Hello, PC!";
        memcpy(lpBuffer, mockResponse.c_str(), mockResponse.size() + 1);
        *lpNumberOfBytesRead = mockResponse.size();
        return TRUE;
    }
    return FALSE;
}

BOOL MockCloseHandle(HANDLE hObject) {
    return (hObject == hMockSerial);
}

// Tests
TEST(InitSerialPortSuccessTest, ValidPort) {
    hSerial = MockCreateFileW(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr); // COM3
    EXPECT_NE(hSerial, INVALID_HANDLE_VALUE);
}

TEST(InitSerialPortFailureTest, InvalidPort) {
    hSerial = MockCreateFileW(L"INVALID_PORT", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    EXPECT_EQ(hSerial, INVALID_HANDLE_VALUE);
}

TEST(SendMessageSuccessTest, ValidHandle) {
    const char* message = "Hello, Arduino!";
    DWORD bytesWritten = 0;
    BOOL success = MockWriteFile(hMockSerial, message, strlen(message), &bytesWritten, nullptr);
    EXPECT_TRUE(success);
    EXPECT_EQ(bytesWritten, strlen(message));
}

TEST(SendMessageFailureTest, InvalidHandle) {
    const char* message = "Hello, Arduino!";
    DWORD bytesWritten = 0;
    BOOL success = MockWriteFile(INVALID_HANDLE_VALUE, message, strlen(message), &bytesWritten, nullptr);
    EXPECT_FALSE(success);
}

TEST(ReceiveMessageSuccessTest, ValidHandle) {
    char buffer[1024] = { 0 };
    DWORD bytesRead = 0;
    BOOL success = MockReadFile(hMockSerial, buffer, sizeof(buffer), &bytesRead, nullptr);

    EXPECT_TRUE(success);
    EXPECT_EQ(std::string(buffer), "Hello, PC!");
    EXPECT_EQ(bytesRead, 10);
}

TEST(ReceiveMessageFailureTest, InvalidHandle) {
    char buffer[1024] = { 0 };
    DWORD bytesRead = 0;
    BOOL success = MockReadFile(INVALID_HANDLE_VALUE, buffer, sizeof(buffer), &bytesRead, nullptr);

    EXPECT_FALSE(success);
    EXPECT_EQ(bytesRead, 0);
}

TEST(CloseSerialPortSuccessTest, ValidHandle) {
    BOOL success = MockCloseHandle(hMockSerial);
    EXPECT_TRUE(success);
}

TEST(CloseSerialPortFailureTest, InvalidHandle) {
    BOOL success = MockCloseHandle(INVALID_HANDLE_VALUE);
    EXPECT_FALSE(success);
}

// Integration test
TEST(SerialIntegrationTest, FullWorkflow) {
    initSerialPort("COM3");

    const char* message = "Integration Test";
    sendMessage(message);

    std::string receivedMessage = receiveMessage();
    EXPECT_EQ(receivedMessage, "Arduino ready\r\n");

    closeSerialPort();
}