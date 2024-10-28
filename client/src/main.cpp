#include <iostream>
#include <string>
#include "serial.h"

using namespace std;

int main() {
    // Use the correct COM port (replace "COM3" with your port)
    initSerialPort("\\\\.\\COM3");

    // Send message
    sendMessage("Hello, Arduino!\n");

    // Wait to allow Arduino to process the message
    Sleep(1000);

    // Attempt to receive response
    string response = receiveMessage();
    if (!response.empty()) {
        cout << "Received from Arduino: " << response << endl;
    }
    else {
        cout << "No response received." << endl;
    }

    // Close the port
    closeSerialPort();

    return 0;
}