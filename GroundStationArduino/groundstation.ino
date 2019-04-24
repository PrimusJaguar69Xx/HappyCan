#define COMM_BAUD_RATE 9600

#include <SoftwareSerial.h> // Used for comm with radio

#define NO_WIN
#include "C:\Users\jacob\Documents\Arduino\libraries\Data.h"



// BUFFER ReadFromSat
mINSTRUCTION ReadPcBuffer; // BUFFER ReadFromPC

mDATA WritePcBuffer; // BUFFER WriteToPC
// BUFFER WriteToSatelite


void setup() 
{
	Serial.begin(COMM_BAUD_RATE);
}

void loop()
{
    unsigned long __STARTTIME = millis(); // TIMING

    if ((Serial.available() / sizeof(mINSTRUCTION)) >= 1) {
        byte tempBuffer[sizeof(mINSTRUCTION)];
        for(int i = 0; i < sizeof(mINSTRUCTION); i++)
            tempBuffer[i] = Serial.read();

        memcpy(&ReadPcBuffer, tempBuffer, 8);

        // Act on instruction from PC (ReadPcBuffer)

    }

    // Fill mDATA (WritePcBuffer) with data here

    WritePcBuffer.TIME_STAMP = millis();
    WritePcBuffer.Air_Pressure = 27;

    // Send the data

    WritePcBuffer.nTest = TEST_NUMBER;
    Serial.write((const uint8_t*) &WritePcBuffer, sizeof(mDATA)); // Send data

    long __LOOPTIME =  millis() - __STARTTIME; // Used too try and get every loop as close to the length of UPLOAD_INTERVAL as possible.

    delay(UPLOAD_INTERVAL - __LOOPTIME);
}

// Serial.write((const uint8_t*) &WritePcBuffer, sizeof(mDATA)); // The way to send data to the program running on the PC
