#include "ArduinoSerial.h"

ArduinoSerial::ArduinoSerial() {
	this->bConnected = false;
	memset(&BufferRead, '\0', BUFFER_READ_SIZE);
}

ArduinoSerial::~ArduinoSerial() {
	CloseHandle(serialDeviceHandle);
}



int ArduinoSerial::ConnectToArduino(std::string ComPort) { // Sets up the device handle to communicate with an arduino on the specified ComPort

	bool tRes = true; // Used for error checking

	serialDeviceHandle = CreateFile(ComPort.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (serialDeviceHandle == INVALID_HANDLE_VALUE) {
		return -1; // Caller should yse GetLastError when -1 is returned
	}

	tRes = GetCommState(serialDeviceHandle, &serialDeviceSettings);
	if(tRes == NULL){
		return -1;
	}

	serialDeviceSettings.BaudRate = CBR_9600;
	serialDeviceSettings.ByteSize = 8;
	serialDeviceSettings.Parity = NOPARITY;
	serialDeviceSettings.fDtrControl = DTR_CONTROL_ENABLE;
	serialDeviceSettings.StopBits = ONESTOPBIT;

	tRes = SetCommState(serialDeviceHandle, &serialDeviceSettings);
	if (tRes == NULL) {
		return -1;
	}

	tRes = PurgeComm(serialDeviceHandle, PURGE_RXCLEAR | PURGE_TXCLEAR);
	if (tRes == NULL) {
		return -1;
	}

	bConnected = true;

	return 0;
}


mDATA ArduinoSerial::ReadFromSerial() { // Returns pointer to internal buffer, if mDATA.nTest is < 0 an error occured or there wasnt any data to be read

	int tRes = false; // Used for errorchecking only

	DWORD errors;
	int bytesToRead = 0;
	DWORD bytesRead = 0;

	mDATA rValue;
	memset(&rValue, NULL, sizeof(mDATA));

	tRes = ClearCommError(serialDeviceHandle, &errors, &serialDeviceInfo); // Gets an update in the serial port, ie. gets the que
	if (tRes == NULL) {
		rValue.nTest = -1;
		return rValue;
	}

	if (serialDeviceInfo.cbInQue > 0) { // Tests if there is any data in read queue
		if (serialDeviceInfo.cbInQue % sizeof(mDATA) == NULL)
			bytesToRead = sizeof(mDATA);
		else {
			tRes = PurgeComm(serialDeviceHandle, PURGE_RXCLEAR); // This aligns it if its isnt perfect
			rValue.nTest = -1;
			return rValue;
		}

		tRes = ReadFile(serialDeviceHandle, &rValue, sizeof(mDATA), &bytesRead, NULL); // Gets the data
		if (tRes == NULL) {
			rValue.nTest = bytesRead - sizeof(mDATA);
			return rValue;
		}

		if (rValue.nTest == TEST_NUMBER) { // Maybe implement an iterator instead of a test value
			return rValue;
		}
		else {
			rValue.nTest = -1;
			return rValue;
		}
	}
	else { // if no data in the que
		rValue.nTest = -1;
		return rValue;
	}
}


// #################

DWORD ArduinoSerial::WriteToSerial(mINSTRUCTION data) {

	int tRes = 0;

	DWORD bytesWritten;
	
	tRes = PurgeComm(serialDeviceHandle, PURGE_RXCLEAR); // Clear the write buffer
	if (tRes == NULL) {
		return -1;
	}

	tRes = WriteFile(serialDeviceHandle, &data, sizeof(data), &bytesWritten, NULL);
	if (tRes == NULL)
		return -1;

	return bytesWritten;
}