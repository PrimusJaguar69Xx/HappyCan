#pragma once

#include <string>

#include <windows.h>

#include "C:\Users\jacob\Documents\Arduino\libraries\Data.h"
#include "hSatelite.h"

#define ARDUINO_BAUD_RATE 9600
#define BUFFER_READ_SIZE 64

class ArduinoSerial {
private:
	bool bConnected;

	DCB serialDeviceSettings;
	HANDLE serialDeviceHandle;
	COMSTAT serialDeviceInfo;

	char BufferRead[BUFFER_READ_SIZE];
public:

	ArduinoSerial();
	~ArduinoSerial();

	int ConnectToArduino(std::string ComPort);
	
//	int ReadFromSerial(char** pointerToBuffer); // aendre maaden til at returne data'en
	mDATA ReadFromSerial();
	DWORD WriteToSerial(mINSTRUCTION data); 

	bool Connected() { // Check if the arduino is still there
		return bConnected;
	}

	int GetElementsInReadQue() {
		return serialDeviceInfo.cbInQue / sizeof(mDATA);
	}
};