# 1 "c:\\Users\\jacob\\Documents\\CanSat 2019\\GroundStationArduino\\groundstation.ino"
# 1 "c:\\Users\\jacob\\Documents\\CanSat 2019\\GroundStationArduino\\groundstation.ino"


# 4 "c:\\Users\\jacob\\Documents\\CanSat 2019\\GroundStationArduino\\groundstation.ino" 2


# 7 "c:\\Users\\jacob\\Documents\\CanSat 2019\\GroundStationArduino\\groundstation.ino" 2



// BUFFER ReadFromSat
mINSTRUCTION ReadPcBuffer; // BUFFER ReadFromPC

mDATA WritePcBuffer; // BUFFER WriteToPC
// BUFFER WriteToSatelite


void setup()
{
 Serial.begin(9600);
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

    WritePcBuffer.nTest = 25835019;
    Serial.write((const uint8_t*) &WritePcBuffer, sizeof(mDATA)); // Send data

    long __LOOPTIME = millis() - __STARTTIME; // Used too try and get every loop as close to the length of UPLOAD_INTERVAL as possible.

    delay(200 - __LOOPTIME);
}

// Serial.write((const uint8_t*) &WritePcBuffer, sizeof(mDATA)); // The way to send data to the program running on the PC
